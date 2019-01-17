#ifndef DRAW_H
#define DRAW_H

#include "./../include/utils.hpp"

using namespace cv;
using namespace std;

class Image;

void draw_rectangle(Image image, Point top_left, int height, int width, int intensity);
vector<Point> draw_line_low(Point start, Point end);
vector<Point> draw_line_high(Point start, Point end);
vector<Point> draw_1line(Point start, Point end);

#endif
