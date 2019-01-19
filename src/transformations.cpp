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

        Mat invertAffineMat(Mat_<double> m){
                return (1/(m(0,0)*m(1,1) - m(0,1)*m(1,0)))*
                        (Mat)(Mat_<double>(2,3) <<  
                         m(1,1),     -m(0,1),    m(0,1)*m(1,2) - m(0,2)*m(1,1),
                        -m(1,0),      m(0,0),    m(0,2)*m(1,0) - m(0,0)*m(1,2));
        }

        void rotate(Image& img,
                    double theta, double xc, double yc,
                    interpolation::interpolationType type){
                std::cout << xc << " " << yc << std::endl;
                Mat rot = generateRotationMatrix(theta, xc, yc);
                std::cout << rot << endl;
                rot = invertAffineMat(rot);
                std::cout << rot << endl;
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
}
}

void symmetryy(Image image, string filename)
{ //axis = 0 --> y axis, axis = 1 --> x axis
  Mat imagemat = image.getmat();
  Size taille = image.getsize();
  Mat modified_img(taille, CV_8U);
  for (int x = 0; x < taille.width; x++){
    for (int y = 0; y < taille.height;y++){
      modified_img.at<uchar>(Point(x,y)) = imagemat.at<uchar>(Point(taille.width-1-x,y));
    }
  }
  savemat(modified_img, filename);
}

void symmetryx(Image image, string filename)
{ //axis = 0 --> y axis, axis = 1 --> x axis
  Mat imagemat = image.getmat();
  Size taille = image.getsize();
  Mat modified_img(taille, CV_8U);
  for (int x = 0; x < taille.width; x++){
    for (int y = 0; y < taille.height;y++){
      modified_img.at<uchar>(Point(x,y)) = imagemat.at<uchar>(Point(x, taille.height-1-y));
    }
  }
  savemat(modified_img, filename);
}

double lowerfunc(Point point1, Point point2, double K)
{
  //double result = 1/(1+exp(K*(distance(point1, point2)- 120)));
  double result = 1/(1+exp((K+K*abs(costheta(point1, point2)))*(distance(point1, point2) - 120 + abs(costheta(point1, point2)) * 50)));
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
    }
  }
  image.setmat(immat);
}
