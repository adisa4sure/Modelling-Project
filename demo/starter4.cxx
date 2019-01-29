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


Image erosion(Image image, Kernel kernel, int threshold){
    Image output = image.clone();
    output.binarization(threshold);
    Mat output_mat = output.getmat();
    Size s = image.getsize();
    int dim = kernel.getdim();
    Point orig = kernel.getorig();
    output.setmat(output_mat);
    return output;
}

Image dilatation(Image image, Kernel kernel, int threshold){
    Image output = image.clone();
    output.binarization(threshold);
    Size s = image.getsize();
    Point orig = kernel.getorig();
    for (unsigned int i = 0; i < s.width; i++){
        for (unsigned int j = 0; j < s.height; j++){
            Mat extract(image.getmat(), Rect(i - orig.x, j - orig.y, kernel.getdim(), kernel.getdim()));
            (output.getmat()).at<uchar>(i,j) = kernel.dilate(extract);
      }
  }
  return output;
}

int main(){
    Image image("./images/clean_finger.png");
    Kernel kernel(3, 1, 1, "Square");
    Image test = erosion(image, kernel, 127);
    test.grayscale();
    test.show();
    libfp::utils::waitKey(0);
}
