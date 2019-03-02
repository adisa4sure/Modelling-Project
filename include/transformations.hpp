#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <functional>
#include "draw.hpp"
#include "interpolation/interpolation.hpp"

using namespace cv;
using namespace std;

using namespace libfp;

namespace libfp {
namespace transformations {
        typedef std::function<Mat(Mat)> mapfun;

        /*!
         *  \brief Saves an image
         *
         *  Saves the image contained in mat to a new file
         *
         *  \param mat : the Mat to save in a new file
         *  \param filename : the path+filename in which we save the image
         */
        void remap(Image& img, mapfun fn, interpolation::interpolationType type);
        /*!
         *  \brief Saves an image
         *
         *  Saves the image contained in mat to a new file
         *
         *  \param mat : the Mat to save in a new file
         *  \param filename : the path+filename in which we save the image
         */
        mapfun lmat2map(Mat mat);
        /*!
         *  \brief Saves an image
         *
         *  Saves the image contained in mat to a new file
         *
         *  \param mat : the Mat to save in a new file
         *  \param filename : the path+filename in which we save the image
         */
        mapfun amat2map(Mat mat);
        /*!
         *  \brief Saves an image
         *
         *  Saves the image contained in mat to a new file
         *
         *  \param mat : the Mat to save in a new file
         *  \param filename : the path+filename in which we save the image
         */
        Mat getRotationMatrix(double, double, double);
        /*!
         *  \brief Saves an image
         *
         *  Saves the image contained in mat to a new file
         *
         *  \param mat : the Mat to save in a new file
         *  \param filename : the path+filename in which we save the image
         */
        Mat invertAffineMat(Mat_<double>);
        /*!
         *  \brief Saves an image
         *
         *  Saves the image contained in mat to a new file
         *
         *  \param mat : the Mat to save in a new file
         *  \param filename : the path+filename in which we save the image
         */
        void rotate(Image&, double, double, double, interpolation::interpolationType);
        /*!
         *  \brief Saves an image
         *
         *  Saves the image contained in mat to a new file
         *
         *  \param mat : the Mat to save in a new file
         *  \param filename : the path+filename in which we save the image
         */
        Mat generateAmatFromPoints(vector<Mat>, vector<Mat>);
         /*!
          *  \brief Symmmetry/y
          *
          *  Performs a symmetry along the y axis on the given image
          *
          *  \param image : the image to modify
          */
        void symmetryy(Image& image);
        /*!
         *  \brief Symmetry/x
         *
         *  Performs a symmetry along the x axis on the given image
         *
         *  \param image : the image to modify
         */
        void symmetryx(Image& image);
         /*!
          *  \brief Sigmoid
          *
          *  Returns the evaluation of the function used to simulate a weaken pressure
          *  in point2, given the center point1
          *  \f{equation}{
          *   c(x,y) = \frac{1}{1+e^{(K + K*|cos(\theta (x,y))|)*(r(x,y)-s)}}
          *   \f}
          *
          *  \param point1 : center
          *  \param point2 : point to modify
          */
        double lowerfunc(Point point1, Point point2);
        /*!
         *  \brief Weaker pressure
         *
         *  Simulates a weaker pressure on the given image
         *
         *  \param image : Image to modify
         *  \param center : center of the transformation, should be localized near the center of the fingerprint
         *  \param width : width of the rectangle to modify
         *  \param height : height of the rectangle to modify
         *  \param K : parameter for the lower_func used
         *  \param s : parameter for the lower_func used
         */
        void weaken_pressure(Image image, Point center, int width, int height, double K, int s);
        /*!
         *  \brief Blur
         *
         *  Blurs the image using the Fourier convolution
         *
         *  \param image : the image to modify
         *  \param ksize : size of the Gaussian kerel used to blur the image
         */
        void blur_fc(Image &image, int ksize);
        /*!
         *  \brief Blur
         *
         *  Blurs the image using the greedy convolution
         *
         *  \param image : the image to modify
         *  \param ksize : size of the Gaussian kerel used to blur the image
         */
        void blur_gc(Image &image, int ksize);
        /*!
         *  \brief Negative
         *
         * Inverts the grayscale : black and whites are permuted
         *
         *  \param image : the image to modify
         */
        void negative(Image& image);
        /*!
         *  \brief Erosion filtering
         *
         *  Performs the erosion operation on an image given a kernel.
         *  This methods converts images in black and white.
         *
         *  \param image : Image to modify
         *  \param kernel : kernel(or mask) applied to the image in order to filter it
         *  \param threshold : threshold used for the binarization of the image
         */
        Image erosion(Image& image, Kernel kernel, int threshold);
        /*!
         *  \brief Dilatation filtering
         *
         *  Performs the erosion operation on an image given a kernel.
         *  This methods converts images in black and white.
         *
         *  \param image : Image to modify
         *  \param kernel : kernel(or mask) applied to the image in order to filter it
         *  \param threshold : threshold used for the binarization of the image
         */
        Image dilatation(Image& image, Kernel kernel, int threshold);
        /*!
         *  \brief Grayscale erosion filtering
         *
         *  Performs the erosion operation on an image given a kernel.
         *
         *  \param image : Image to modify
         *  \param kernel : kernel(or mask) applied to the image in order to filter it
         */
        Image gray_erosion(Image& image, Kernel kernel);
        /*!
         *  \brief Grayscale dilatation filtering
         *
         *  Performs the erosion operation on an image given a kernel.
         *
         *  \param image : Image to modify
         *  \param kernel : kernel(or mask) applied to the image in order to filter it
         */
        Image gray_dilatation(Image& image, Kernel kernel);
}
}


#endif
