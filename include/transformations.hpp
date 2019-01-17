#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "draw.hpp"

using namespace cv;
using namespace std;

void symmetry(Image image, string filename);
void symmetryx(Image image, string filename);
double lowerfunc(Point point1, Point point2);
void weaken_pressure(Image image, Point center, int width, int height, double K);

#endif
