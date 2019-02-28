#include "transformations.hpp"

int main()
{
  Image image("./images/clean_finger.png");
  Image image2("./images/clean_finger.png");
  for(int i = 0; i < 8; i++)
  {
    libfp::transformations::blur_gc(image2, 10);
    libfp::transformations::blur_fc(image, 10);
  }
  imshow("resultfc", image.getmat());
  imshow("resultgc", image2.getmat());
  libfp::utils::savemat(image.getmat(), "8_conv_fc");
  libfp::utils::savemat(image2.getmat(), "8_conv_gc");
  libfp::utils::waitKey(0);
  //savemat(image.getmat(), "convoluted");
  //image.show("convolution");
  return(0);
}
