#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "interpolation/interpolator.hpp"

using namespace cv;
using namespace std;

namespace libfp {
namespace transformations {
        typedef cv::Mat (*mapfun)(cv::Mat);

        void remap(Image& img, mapfun fn, interpolation::interpolationType type);
}
}

void symmetry(Image image, string filename);
void symmetryx(Image image, string filename);
double lowerfunc(Point point1, Point point2);
void weaken_pressure(Image image, Point center, int width, int height, double K);

#endif
