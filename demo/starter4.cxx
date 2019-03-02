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

int main(){
    Image image("./Images_test_bin/erosion_dilatation.png");
    Kernel kernel(3, 1, 1, "Plus");
    int threshold = (int) mean(image.getmat())[0];
    Image test = libfp::transformations::dilatation(image, kernel, threshold);
    imwrite("./Images_test_bin/erosion_dilatation.png", test.getmat());
    test.show();
    libfp::utils::waitKey(0);
}
