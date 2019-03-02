#include "transformations.hpp"
#include <cstdlib>

int main()
{
  Mat tnoise(Size(256,288), CV_8U, Scalar(0));
  for (int i = 0; i < tnoise.size().width; i++)
  {
    for (int j = 0; j < tnoise.size().height; j++)
    {
      tnoise.at<uchar>(j,i) = (rand()%2)*255;
    }
  }
  Image image("./images/clean_finger.png");
  Image noise("./images/perlin-noise.png");
  //Image noise(tnoise, "noise");
  // for (int i = 0; i < 8; i++)
  // {
  //   libfp::transformations::blur_gc(noise, 3);
  // }
  image.apply_noise(noise);
  namedWindow("image");
  namedWindow("noise");
  imshow("image", image.getmat());
  imshow("noise", noise.getmat());
  libfp::utils::waitKey(0);
}
