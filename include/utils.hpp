#ifndef UTILS_H
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>

#include "draw.hpp"

namespace libfp{
    namespace utils{
        int waitKey(int);
    }
}

class Image
{
    private:
        cv::Mat mat;
        int height;
        int width;
        std::string window_name;
    public:
        Image(std::string filename);
        Image clone();
        void show(std::string force_window_name = "");
        cv::Mat getmat() const;
        void setmat(cv::Mat newmat);
        cv::Size getsize() const;
        void convolve(cv::Mat filter, bool half);
        void registerCallback(cv::MouseCallback callback, void* userdata = 0);
};

void savemat(cv::Mat mat, std::string filename);

double distance(cv::Point point1, cv::Point point2);

double costheta(cv::Point point1, cv::Point point2);

bool parity(unsigned  int x);

#endif
