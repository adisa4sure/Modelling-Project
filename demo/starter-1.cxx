#include <opencv2/opencv.hpp>
#include "utils.hpp"
#include "transformations.hpp"
#include "draw.hpp"
#include "interpolation/interpolation.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <iterator>
#include "interpolation/interpolation.hpp"
#include <cmath>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
  if(argc !=2) //checking for required arguments
  { //error msg for incomplete argument
    cout << "usage" <<argv[0] << "[Image to load]" <<endl;
    return -1;
  }

  //reading an in image
  Image image = Image(argv[1]);
  if(image.getmat().empty()) //checking for availabilty of the image
  {
    cout << "could not load the image" <<argv[1] << endl; //error msg
    return -1;
  }
  //Mat image = imread(argv[1], IMREAD_GRAYSCALE);
  //Mat output = image.clone();

  // Draw a rectangle ( 5th argument is not +ve)
  draw_rectangle(image, Point(34,116), 65, 90, 255);
  draw_rectangle(image, Point(170,195), 65, 35, 0);
  //rectangle( output, Point( 30, 125 ), Point( 105, 180), Scalar( 255, 155, 25 ), -1, 1 );
  //imshow("Image1",image);

  Image image5 = image.clone();
  Image image6 = image.clone();
  Image image7 = image.clone();
  libfp::transformations::negative(image5, "texty"); //negative effect
  libfp::transformations::symmetryx(image6, "textx"); //symmetry about X-axis
  libfp::transformations::symmetryy(image7, "texty"); //symmetry about Y-axis


  //definition&initialization of image2,3&4
  // Mat image1 = image.getmat();
  // Mat image2 = image.getmat();
  // Mat image3 = image.getmat();
  // Mat image4 = image.getmat();

  //for negative effect on an image
  // for(int i = 0; i<image.getmat().rows; i++){
  //   for(int j=0; j<image.getmat().cols; j++){
  //     image1.at<uchar>(i, j) = 255 - image.getmat().at<uchar>(i, j);
  //   }
  // }
  // //symmetry about X-axis
  // for(int i = 0; i<image.getmat().rows; i++){
  //   for(int j=0; j<image.getmat().cols; j++){
  //     image2.at<uchar>(i, j) = image.getmat().at<uchar>(image.getmat().rows -i, j);
  //   }
  // }
  /// //symmetry about Y-axis
  // for(int i = 0; i<image.getmat().rows; i++){
  //   for(int j=0; j<image.getmat(); j++){
  //     image3.at<uchar>(i, j) = image.getmat().at<uchar>(i, image.getmat().cols -j);
  //   }
  // }


  // //displaying images
  image.show("Rec_Source");
  image5.show("Negative");
  image6.show("SymetricX");
  image7.show("SymetricY");

  //namedWindow("Rec_Source",WINDOW_AUTOSIZE);
  // imshow("Rec_Source", image.getmat());
  // imshow("Negative", image1);
  // imshow("SymetricX", image2);
  // imshow("SymetricY", image3);


  //saving images
  libfp::utils::savemat(image.getmat(), "Rec_Source");
  libfp::utils::savemat(image5.getmat(), "SymetricY");
  libfp::utils::savemat(image6.getmat(), "SymetricX");
  libfp::utils::savemat(image7.getmat(), "SymetricY");
  // imwrite("Rec_Source.png", image1);
  // imwrite("Negative", image2);
  // imwrite("SymetricY.png", image3);
  // imwrite("SymetricX.png", image4);

  libfp::utils::waitKey(0); //waiting key by pressing any key
  return 0;

}
