#include <opencv2/opencv.hpp>
#include "transformations.hpp"
#include "utils.hpp"
#include "interpolation/interpolation.hpp"

namespace libfp {
namespace transformations {
        void _remap(Image& img, mapfun fn, interpolation::Interpolator* inter)
        {
                Mat buf = img.getmat();

                Mat out = cv::Mat::zeros(img.getsize(), buf.type());

                for(unsigned int x = 0; x < img.getsize().width; x++)
                {
                        for(unsigned int y = 0; y < img.getsize().height; y++)
                        {
                                cv::Mat orig = fn((Mat_<double>(2,1) << (double)x, (double)y));
                                double xc, yc;
                                xc = orig.at<double>(0,0);
                                yc = orig.at<double>(1,0);
                                out.at<uchar>(y, x) = inter->get_pixel_value(img, xc, yc);
                        }
                }
                img.setmat(out);
        }

        void remap(Image& img, mapfun fn, interpolation::interpolationType type)
        {
                interpolation::Interpolator* inter;
                switch(type)
                {
                        case interpolation::interpolationType::INTERPOLATION_BILINEAR:
                                inter = new interpolation::LinearInterpolator();
                                break;
                        case interpolation::interpolationType::INTERPOLATION_LANCZOS2:
                                inter = new interpolation::LanczosInterpolator(2);
                                break;
                        case interpolation::interpolationType::INTERPOLATION_LANCZOS3:
                                inter = new interpolation::LanczosInterpolator(3);
                                break;
                        case interpolation::interpolationType::INTERPOLATION_LANCZOS4:
                                inter = new interpolation::LanczosInterpolator(4);
                                break;
                }

                _remap(img, fn, inter);
                delete inter;
        }

        mapfun lmat2map(Mat mat){
                return [=](Mat p) -> Mat { return mat*p; };
        }

        mapfun amat2map(Mat mat){
                return [=](Mat p) -> Mat {
                        Mat emat;
                        vconcat(mat, (Mat)(Mat_<double>(1,3) << 0, 0, 1), emat);
                        Mat ep;
                        vconcat(p, (Mat)(Mat_<double>(1,1) << 1), ep);
                        return ((Mat)(emat*ep))(Range(0,2), Range::all());
                };
        }

        Mat generateTranslationMatrix(double tx, double ty){
               return (Mat)(Mat_<double>(2,3) << 1, 0, tx, 0, 1, ty);
        }

        Mat generateOrigRotationMatrix(double theta){
                double c, s;
                c = std::cos(theta);
                s = std::sin(theta);
                return (Mat)(Mat_<double>(2,3) << c, -s, 0, s, c, 0);
        }

        Mat generateRotationMatrix(double theta, double xc, double yc){
                Mat fTrans, bTrans, rot;
                Mat lastLine = (Mat_<double>(1,3) << 0, 0, 1);
                vconcat(generateTranslationMatrix(xc, yc), lastLine, fTrans);
                vconcat(generateTranslationMatrix(-xc, -yc), lastLine, bTrans);
                vconcat(generateOrigRotationMatrix(theta), lastLine, rot);
                return ((Mat)(fTrans*rot*bTrans))(Range(0,2), Range::all());
        }

        mapfun generateWarpSkinMapping(double thetamax, double xc, double yc, double k){
                return [=](Mat d) -> Mat {
                        double x = d.at<double>(0,0);
                        double y = d.at<double>(0,1);
                        double dx = x-xc;
                        double dy = y-yc;
                        std::function<double(double)> regulator = [](double x) -> double { return -2*std::pow(x,3) + 3*std::pow(x,2); };
                        double r = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
                        double beta = std::atan2(dy, dx) + thetamax*regulator((k-r)/k);
                        std::function<double(double)> regulatord = [](double x) -> double { return -1*std::pow(x,3) + 2*std::pow(x,2); };
                        double rr = regulatord(r/k)*k;//rectified r
                        Mat out = (Mat_<double>(2,1) << ((r <= k) ? xc + rr*std::cos(beta) : x), ((r <= k) ? yc + rr*std::sin(beta) : y));
                        return out;
                };
        }

        Mat invertAffineMat(Mat_<double> m){
                return (1/(m(0,0)*m(1,1) - m(0,1)*m(1,0)))*
                        (Mat)(Mat_<double>(2,3) <<
                         m(1,1),     -m(0,1),    m(0,1)*m(1,2) - m(0,2)*m(1,1),
                        -m(1,0),      m(0,0),    m(0,2)*m(1,0) - m(0,0)*m(1,2));
        }

        void rotate(Image& img,
                    double theta, double xc, double yc,
                    interpolation::interpolationType type){
                Mat rot = generateRotationMatrix(theta, xc, yc);
                rot = invertAffineMat(rot);
                remap(img, amat2map(rot), type);
        }

        Mat generateAmatFromPoints(vector<Mat> srcs, vector<Mat> dsts){
                Mat_<double> omat = Mat_<double>(2,3);
                Mat_<double> s1, s2, s3, d1, d2, d3;
                s1 = srcs[0];
                s2 = srcs[1];
                s3 = srcs[2];
                d1 = dsts[0];
                d2 = dsts[1];
                d3 = dsts[2];
                double d = s1(0,0)*(s3(0,1) - s2(0,1)) + s2(0,0)*(s1(0,1) - s3(0,1)) + s3(0,0)*(s2(0,1) - s1(0,1));

                omat(0,0) = (1./d)*(s1(0,1)*(d2(0,0) - d3(0,0)) + s2(0,1)*(d3(0,0) - d1(0,0)) + s3(0,1)*(d1(0,0) - d2(0,0)));
                omat(0,1) = (1./d)*(s1(0,0)*(d3(0,0) - d2(0,0)) + s2(0,0)*(d1(0,0) - d3(0,0)) + s3(0,0)*(d2(0,0) - d1(0,0)));
                omat(1,0) = (1./d)*(s1(0,1)*(d2(0,1) - d3(0,1)) + s2(0,1)*(d3(0,1) - d1(0,1)) + s3(0,1)*(d1(0,1) - d2(0,1)));
                omat(1,1) = (1./d)*(s1(0,0)*(d3(0,1) - d2(0,1)) + s2(0,0)*(d1(0,1) - d3(0,1)) + s3(0,0)*(d2(0,1) - d1(0,1)));
                omat(0,2) = (1./d)*(s1(0,0)*(s3(0,1)*d2(0,0) - s2(0,1)*d3(0,0)) + s2(0,0)*(s1(0,1)*d3(0,0) - s3(0,1)*d1(0,0)) + s3(0,0)*(s2(0,1)*d1(0,0) - s1(0,1)*d2(0,0)));
                omat(1,2) = (1./d)*(s1(0,0)*(s3(0,1)*d2(0,1) - s2(0,1)*d3(0,1)) + s2(0,0)*(s1(0,1)*d3(0,1) - s3(0,1)*d1(0,1)) + s3(0,0)*(s2(0,1)*d1(0,1) - s1(0,1)*d2(0,1)));

                return (Mat)omat;
        }
        void symmetryy(Image image)
        {
          Mat imagemat = image.getmat();
          Size taille = image.getsize();
          Mat modified_img(taille, CV_8U);
          for (int x = 0; x < taille.width; x++){
            for (int y = 0; y < taille.height;y++){
              modified_img.at<uchar>(Point(x,y)) = imagemat.at<uchar>(Point(taille.width-1-x,y));
            }
          }
          image.setmat(modified_img);
        }

        void symmetryx(Image image, string filename)
        {
          Mat imagemat = image.getmat();
          Size taille = image.getsize();
          Mat modified_img(taille, CV_8U);
          for (int x = 0; x < taille.width; x++){
            for (int y = 0; y < taille.height;y++){
              modified_img.at<uchar>(Point(x,y)) = imagemat.at<uchar>(Point(x, taille.height-1-y));
            }
          }
          image.setmat(modified_img);
        }

        double lowerfunc(Point point1, Point point2, double K)
        {
          //double result = 1/(1+exp(K*(distance(point1, point2)- 120)));
          double result = 1/(1+exp((K+K*abs(costheta(point1, point2)))*(distance(point1, point2) - 120 + 30*abs(costheta(point1, point2)))));
          return result;
        }


        void weaken_pressure(Image image, Point center, int width, int height, double K)
        {
          Mat immat = image.getmat();
          //for (int x = center.x - width/2; x < center.x + width/2 + 1; x++)
          for (int x = 0; x < image.getsize().width; x++)
          {
            //for (int y = center.y - height/2; y < center.y + height/2 + 1; y++)
            for (int y = 0; y < image.getsize().height; y++)
            {
              //immat.at<uchar>(Point(x,y)) = immat.at<uchar>(Point(x,y))*lowerfunc(center, Point(x,y), K);
              immat.at<uchar>(Point(x,y)) = 255 - double(255 - immat.at<uchar>(Point(x,y)))*lowerfunc(center, Point(x,y), K);
              //immat.at<uchar>(Point(x,y)) = costheta(center, Point(x,y))*255;
            }
          }
          image.setmat(immat);
        }



}
}
