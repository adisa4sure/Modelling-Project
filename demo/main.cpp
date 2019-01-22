#include "transformations.hpp"

int main()
{
  Image image("clean_finger.png");
  Mat output = image.getmat().clone();
  draw_rectangle(image, Point(0,0), 100, 100, 0);
  //symmetryx(image, "testx");
  //weaken_pressure(image, Point(127, 160), 250, 280, 0.05);
  Mat H(Size(3,3), CV_8U, Scalar(0));
  //Had to initialize that way or I couldn't access the values
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (!parity(i) && !parity(j))
      {
        H.at<uchar>(j,i) = 16;
      } else if (i==1 && j==1)
      {
        H.at<uchar>(j,i) = 64;
      } else {
        H.at<uchar>(j,i) = 32;
      }
    }
  }
  cout << "Matrice : " << H << endl;
  //image.convolve(H, 1);
  //dft(image.getmat(), output);
  blur(image.getmat(), output, Size(3,3)); //OpenCV function
  namedWindow("fourier", WINDOW_AUTOSIZE);
  imshow("fourier", output);
  waitKey(0);
  //savemat(image.getmat(), "convoluted");
  image.show("convolution");
  return(0);
}
