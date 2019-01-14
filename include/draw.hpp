#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

class Image
{
private:
  Mat img;
  int height;
  int width;
public:
  Image(string filename);
  void draw_rectangle(Point top_left, int height, int width, int intensity);
  vector<Point> draw_line_low(Point start, Point end, int intensity);
  vector<Point> draw_line_high(Point start, Point end, int intensity);
  vector<Point> draw_1line(Point start, Point end, int intensity);
  void draw_line(Point start, Point end, int );
  void draw_circle(Point center, int radius);
  //void symmetry(string filename, bool axis);
};
