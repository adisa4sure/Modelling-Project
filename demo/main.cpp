#include "transformations.hpp"

int main()
{
  Image image("clean_finger");
  Image image2("clean_finger");
  //draw_rectangle(image, Point(0,0), 100, 100, 0);
  //symmetryx(image, "testx");
  weaken_pressure(image, Point(127, 160), 250, 280, 0.05);
  savemat(image.getmat(), "lightened_iso_fp");
  return(0);
}
