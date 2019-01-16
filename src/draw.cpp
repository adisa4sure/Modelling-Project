#include "./../include/draw.hpp"


Image::Image(string filename)
{
  stringstream ss;
  ss << "./../images/" << filename << ".png";
  string link = ss.str();
  img = imread(link, 0);
}

void Image::draw_rectangle(Point top_left, int height, int width, int intensity)
{
  for(int x = top_left.x; x<x+width; x ++)
  { 
    for(int y = top_left.y; y< y+height; y++)
    {
      img.at<uchar>(Point(x,y)) = intensity;
    }
  }
}

//https://en.wikipedia.org/wiki/Bresenham's_line_algorithm

vector<Point> Image::draw_line_low(Point start, Point end)
{
  vector<Point> line_pixels;
  int dx = end.x - start.x;
  int dy = end.y - start.y;
  int yi = 1;
  if (dy < 0){
    yi = -1;
    dy = -dy;
  }
  int D = 2*dy - dx;
  int y = start.y;
  for(int x = start.x; x < end.x + 1;x++){
    line_pixels.push_back(Point(x,y));
    if (D > 0){
      y = y + yi;
      D = D - 2*dx;
    }
    D = D + 2*dy;
  }
  return(line_pixels);
}

vector<Point> Image::draw_line_high(Point start, Point end)
{
  vector<Point> line_pixels;
  int dx = end.x - start.x;
  int dy = end.y - start.y;
  int xi = 1;
  if (dx < 0){
    xi = -1;
    dx = -dx;
  }
  int D = 2*dx - dy;
  int x = start.x;
  for(int y = start.y; x < end.y + 1;y++){
    line_pixels.push_back(Point(x,y));
    if (D > 0){
      x = x + xi;
      D = D - 2*dy;
    }
    D = D + 2*dx;
  }
  return(line_pixels);
}

vector<Point> Image::draw_1line(Point start, Point end)
{
  if (abs(end.y - start.y) < abs(end.x - start.x)){
    if (start.x > end.x){
      return(this->draw_line_low(end, start));
    } else {
      return(this->draw_line_low(start, end));
    }
  } else {
    if (start.y > end.y){
      return(this->draw_line_high(end, start));
    } else {
      return(this->draw_line_high(start, end));
    }
  }
}
