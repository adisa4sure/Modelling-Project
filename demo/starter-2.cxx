#include <opencv2/opencv.hpp>
#include "utils.hpp"
#include "transformations.hpp"
#include "draw.hpp"
#include "interpolation/interpolation.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <iterator>
#include "interpolation/interpolation.hpp"
#include <cmath>

using namespace cv;
using namespace std;

typedef std::function<void(int, int, int)> mouseCallback;

int main(int argc, char** argv)
{
        if(argc != 3)
        {
                cout << "Usage: " << argv[0] << " [Image 1] [Image 2]" << endl;
                return -1;
        }

        std::vector<Mat> srcs;
        std::vector<Mat> dsts;

        Image imageSrc = Image(argv[1]);

        Image imageDst = Image(argv[2]);
        
        imageDst.show();
        imageSrc.show();

        Mat baseSrc = imageSrc.getmat().clone();
        Mat baseDst = imageDst.getmat().clone();
        
        unsigned int i = 0;

        mouseCallback fn1 = [&srcs, baseSrc, &imageSrc, &i](int event, int x, int y) -> void {
                if(event != cv::EVENT_LBUTTONDOWN)
                        return;


                if(srcs.size() > i){
                        std::cout << "Image 1 -> Changing (" << srcs[i].at<double>(0,0) << ", " << srcs[i].at<double>(0,1) << ") to (" << x << ", " << y << ")" << std::endl;
                        imageSrc.setmat(baseSrc.clone());
                        srcs[i] = (Mat)(Mat_<double>(1,2) << x, y);
                }else{
                        std::cout << "Image 1 -> Setting (" << x << ", " << y << ")" << std::endl;
                        srcs.push_back((Mat)(Mat_<double>(1,2) << x, y));
                }
                
                draw_rectangle(imageSrc, Point(x - 5, y - 5), 10, 10, 0); 
        };

        imageSrc.registerCallback([](int event, int x, int y, int, void* callbackFunc) -> void { 
                (*(mouseCallback*)callbackFunc)(event, x, y);                  
        }, (void*)&fn1);

        mouseCallback fn2 = [&dsts, baseDst, &imageDst, &i](int event, int x, int y) -> void {
                if(event != cv::EVENT_LBUTTONDOWN)
                        return;

                if(dsts.size() > i){
                        std::cout << "Image 2 -> Changing (" << dsts[i].at<double>(0,0) << ", " << dsts[i].at<double>(0,1) << ") to (" << x << ", " << y << ")" << std::endl;
                        imageDst.setmat(baseDst);
                        dsts[i] = (Mat)(Mat_<double>(1,2) << x, y);
                }else{
                        std::cout << "Image 2 -> Setting (" << x << ", " << y << ")" << std::endl;
                        dsts.push_back((Mat)(Mat_<double>(1,2) << x, y));
                }
                draw_rectangle(imageDst, Point(x - 5, y - 5), 10, 10, 0); 
        };

        imageDst.registerCallback([](int event, int x, int y, int, void* callbackFunc) -> void { 
                (*(mouseCallback*)callbackFunc)(event, x, y);                  
        }, (void*)&fn2);

        for(i = 0; i < 3; i++){
                std::cout << "Select pair #" << i << " of corresponding points on each image" << std::endl;

                while((srcs.size() == i) || (dsts.size() == i)){
                        imageDst.show();
                        imageSrc.show();
                        libfp::utils::waitKey(10);
                }
        }

        Mat trans = libfp::transformations::generateAmatFromPoints(srcs, dsts);
        Mat invTrans = libfp::transformations::invertAffineMat(trans);
        std::cout << "Transformation matrix :" << std::endl;
        std::cout << invTrans << std::endl;
        libfp::transformations::remap(imageSrc, libfp::transformations::amat2map(invTrans), libfp::interpolation::INTERPOLATION_LANCZOS4);

        imageSrc.show();
        imageDst.show();
        libfp::utils::waitKey(0);
}
