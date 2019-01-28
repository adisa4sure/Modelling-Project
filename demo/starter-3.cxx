#include "transformations.hpp"
#include <chrono>

int main()
{
  Mat output1, output2, result1, result2, final1, final2;

  Image image("./images/clean_finger.png");
  Image image2("./images/clean_finger.png");
  Image clean("./images/clean_finger.png");
  namedWindow("Difference between reults");
  namedWindow("Fourier, kernel 3x3");
  namedWindow("Greedy convolution, kernel 3x3");

  auto beginningf = chrono::high_resolution_clock::now();

  libfp::transformations::blur_fc(image, 10);

  auto endf = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsedf = endf - beginningf;

  auto beginningc = chrono::high_resolution_clock::now();

  libfp::transformations::blur_gc(image2, 10);

  auto endc = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsedc = endc - beginningc;

  cout << "Fourier convolution time : " << elapsedf.count() << "seconds." << endl;
  cout << "Greedy convolution time : " << elapsedc.count() << "seconds." << endl;

  imshow("Greedy convolution, kernel 3x3", image2.getmat());
  imshow("Clean", clean.getmat());
  imshow("Fourier, kernel 3x3", image.getmat());
  imshow("Difference between results", cv::abs(clean.getmat()-image2.getmat()));
  libfp::utils::waitKey(0);
}
