#include <opencv2/opencv.hpp>
#include "interpolation/lininterpolator.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

namespace libfp{
namespace interpolation{
LinearInterpolator::LinearInterpolator() {}

unsigned char LinearInterpolator::get_pixel_value(Image img, double x, double y) {
        if(x < 0 || x > img.getsize().width || y < 0 || y > img.getsize().height){
                return 255;
        }

        cv::Mat buf = img.getmat();
        int x1, x2, y1, y2;
        x1 = std::floor(x);
        x2 = std::min((int)std::ceil(x), (int)img.getsize().width - 1);
        y1 = std::floor(y);
        y2 = std::min((int)std::ceil(y), (int)img.getsize().height - 1);

        if(!((x2-x1)*(y2-y1))){
                return buf.at<uchar>(x1, y1);
        }

        cv::Mat M = (cv::Mat_<double>(2,2) << (double)buf.at<uchar>(y1, x1),
                                              (double)buf.at<uchar>(y2, x1),
                                              (double)buf.at<uchar>(y1, x2),
                                              (double)buf.at<uchar>(y2, x2));

        cv::Mat X = (cv::Mat_<double>(1,2) << (double)(x2 - x), (double)(x - x1));
        cv::Mat Y = (cv::Mat_<double>(2,1) << (double)(y2 - y), (double)(y - y1));
        double interpolatedIntensity = (1/((x2-x1)*(y2-y1))) * ((cv::Mat)(X * M * Y)).at<double>(0);

        return (unsigned char)std::round(interpolatedIntensity);
}
}
}
