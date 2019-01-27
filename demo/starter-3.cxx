#include "transformations.hpp"

int main()
{
  Image image("./images/clean_finger.png");
  namedWindow("Fourier, kernel 10x10");
  namedWindow("Fourier, kernel 3x3");
  Mat ff = fourier(image.getmat());
  Mat ker1ff = fourier(fill_ker(gaus_ker(10), image.getsize()));
  Mat ker2ff = fourier(fill_ker(gaus_ker(3), image.getsize()));
  Mat output1, output2, result1, result2, final1, final2;
  mulSpectrums(ff, ker1ff, output1, 0);
  mulSpectrums(ff, ker2ff, output2, 0);
  idft(output1, result1, DFT_REAL_OUTPUT);
  idft(output2, result2, DFT_REAL_OUTPUT);
  result1.convertTo(final1, CV_8U);
  result2.convertTo(final2, CV_8U);
  shift(final1);
  shift(final2);
  imshow("Fourier, kernel 10x10", final1);
  imshow("Fourier, kernel 3x3", final2);
  imshow("Clean", image.getmat());
  libfp::utils::waitKey(0);
}
