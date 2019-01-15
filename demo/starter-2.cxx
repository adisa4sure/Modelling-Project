#include <opencv2/opencv.hpp>
#include "utils.hpp"
#include "transformations.hpp"
#include "interpolation/interpolation.hpp"
#include <cmath>

using namespace cv;
using namespace std;

Mat rotMap(Mat p){
        Mat M = (Mat_<double>(2,2) << cos(0.2), -sin(0.2), sin(0.2), cos(0.2));
        Mat d = M*p;
        return d;
}

int main(int argc, char** argv)
{
        if(argc != 2)
        {
                cout << "Usage: " << argv[0] << " [Image to load]" << endl;
                return -1;
        }

        Image image = Image(argv[1]);
        libfp::transformations::remap(image, rotMap, libfp::interpolation::INTERPOLATION_BILINEAR);
        image.show();
        return 0;
}
