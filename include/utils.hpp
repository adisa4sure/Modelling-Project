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

class Image
{
private:
  Mat mat;
  int height;
  int width;
public:
  Image(string filename);
  void show(string windowname);
  Mat getmat();
  void setmat(Mat newmat);
  Size getsize();
  void convolve(Mat filter, bool half);
};

void savemat(Mat mat, string filename);

double distance(Point point1, Point point2);

double costheta(Point point1, Point point2);

bool parity(unsigned  int x);

#endif
