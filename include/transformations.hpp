#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "interpolation/interpolation.hpp"

using namespace cv;
using namespace std;

namespace libfp {
namespace transformations {
        //typedef cv::Mat (*mapfun)(cv::Mat);
        typedef std::function<Mat(Mat)> mapfun;

        void remap(Image& img, mapfun fn, interpolation::interpolationType type);

        mapfun lmat2map(Mat mat);

        mapfun amat2map(Mat mat);

        Mat getRotationMatrix(double, double, double);

        Mat invertAffineMat(Mat_<double>);

        void rotate(Image&, double, double, double, interpolation::interpolationType); 

        Mat generateAmatFromPoints(vector<Mat>, vector<Mat>);
}
}

void symmetry(Image image, string filename);
void symmetryx(Image image, string filename);
double lowerfunc(Point point1, Point point2);
void weaken_pressure(Image image, Point center, int width, int height, double K);

#endif
