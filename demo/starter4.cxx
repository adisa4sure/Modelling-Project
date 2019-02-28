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
    image.binarization(threshold);
    Mat output_mat = output.getmat();
    Size s = image.getsize();
    int dim = kernel.getdim();
    Point orig = kernel.getorig();
    for(unsigned int i = orig.x; i <= s.width - dim + orig.x; i++){
        for(unsigned int j = orig.y; j <= s.height- dim + orig.y; j++){
            Mat extract(image.getmat(), Rect(i - orig.x, j-orig.y, dim, dim));
            output_mat.at<uchar>(j,i) = kernel.erode(extract);
        }
    }
    output.setmat(output_mat);
    image.grayscale();
    output.grayscale();
    return output;
}

Image dilatation(Image image, Kernel kernel, int threshold){
    Image output = image.clone();
    output.binarization(threshold);
    image.binarization(threshold);
    Mat output_mat = output.getmat();
    Size s = image.getsize();
    int dim = kernel.getdim();
    Point orig = kernel.getorig();
    for(unsigned int i = orig.x; i <= s.width - dim + orig.x; i++){
        for(unsigned int j = orig.y; j <= s.height- dim + orig.y; j++){
            Mat extract(image.getmat(), Rect(i - orig.x, j-orig.y, dim, dim));
            output_mat.at<uchar>(j,i) = kernel.dilate(extract);
        }
    }
    output.setmat(output_mat);
    image.grayscale();
    output.grayscale();
    return output;
}

Image gray_erosion(Image image, Kernel kernel){
    Image output = image.clone();
    Mat output_mat = output.getmat();
    Size s = image.getsize();
    int dim = kernel.getdim();
    Point orig = kernel.getorig();
    for(unsigned int i = orig.x; i < s.width - dim + orig.x; i++){
        for(unsigned int j = orig.y; j < s.height - dim + orig.y; j++){
            Mat extract(image.getmat(), Rect(i - orig.x, j-orig.y, dim, dim));
            output_mat.at<uchar>(j,i) = kernel.erode_gray(extract);
        }
    }
    output.setmat(output_mat);
    return output;
}

Image gray_dilatation(Image image, Kernel kernel){
    Image output = image.clone();
    Mat output_mat = output.getmat();
    Size s = image.getsize();
    int dim = kernel.getdim();
    Point orig = kernel.getorig();
    for(unsigned int i = orig.x; i < s.width - dim + orig.x; i++){
        for(unsigned int j = orig.y; j < s.height - dim + orig.y; j++){
            Mat extract(image.getmat(), Rect(i - orig.x, j-orig.y, dim, dim));
            output_mat.at<uchar>(j,i) = kernel.dilate_gray(extract);
        }
    }
    output.setmat(output_mat);
    return output;
}

int main(){
    Image image("./images/clean_finger.png");
    Kernel kernel(3, 1, 1, "Plus");
    int threshold = 127;
    Image test = erosion(image, kernel, threshold);
    test.show();
    image.show();
    libfp::utils::waitKey(0);
}
