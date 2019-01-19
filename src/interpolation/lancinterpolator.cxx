#include <opencv2/opencv.hpp>
#include "interpolation/lancinterpolator.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

#define PI (double)3.1415926535897932384626433832795028841971693993751058209749445923078164

namespace libfp{
namespace interpolation{
static double lanczos_window(double x, int a){
        if(-a <= x && x <= a){
                if(x == 0){
                        return 1;
                }
                return a*std::sin(PI*x)*std::sin(PI*x/a)/std::pow(PI*x, 2);
        }
        return 0;
}

LanczosInterpolator::LanczosInterpolator(int a) : a(a) {}

unsigned char LanczosInterpolator::get_pixel_value(Image img, double x, double y) {
        if(x < 0 || x > img.getsize().width || y < 0 || y > img.getsize().height){
                return 255;
        }

        cv::Mat buf = img.getmat();
        int x0, y0;
        x0 = std::floor(x);
        y0 = std::floor(y);

        double interpolatedIntensity = 0;
        double colSum;

        for(int xc = std::max(x0 - a + 1, 0); xc <= std::min(x0 + a, img.getsize().width); xc++)
        {
                colSum = 0;
                for(int yc = std::max(y0 - a + 1, 0); yc <= std::min(y0 + a, img.getsize().height); yc++)
                {
                       colSum += (double)buf.at<uchar>(yc, xc) * lanczos_window(y-yc, a); 
                }
                interpolatedIntensity += colSum * lanczos_window(x-xc, a); 
        }
        return (unsigned char)std::max(std::min(std::round(interpolatedIntensity), 255.), 0.);
}
}
}
