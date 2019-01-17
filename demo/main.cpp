#include "transformations.hpp"

int main()
{
  Image image("clean_finger");
  draw_rectangle(image, Point(0,0), 100, 100, 0);
  symmetryx(image, "testx");
  image.show();
  return(0);
}
