#include "draw.hpp"

int main()
{
  Image image("./../images/clean_finger.png");
  image.draw_rectangle(Point(0,0), 100, 100, 255);
  return(0);
}
