#ifndef UTILS_H
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "draw.hpp"

using namespace cv;
using namespace std;

namespace libfp{
namespace utils{
        void waitKey(int);
}
}

class Image
{
private:
  Mat mat;
  int height;
  int width;
  string window_name;
public:
  Image(string filename);
  void show(string force_window_name = "");
  Mat getmat();
  void setmat(Mat newmat);
  Size getsize();
  void convolve(Mat filter, bool half);
  void registerCallback(MouseCallback callback, void* userdata = 0);
};

void savemat(Mat mat, string filename);

double distance(Point point1, Point point2);

double costheta(Point point1, Point point2);

bool parity(unsigned  int x);

#endif
