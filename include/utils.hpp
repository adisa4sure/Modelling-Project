#ifndef UTILS_H
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

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
  void show();
  Mat getmat();
  void setmat(Mat newmat);
  Size getsize();
};

void savemat(Mat mat, string filename);

#endif
