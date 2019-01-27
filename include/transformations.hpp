#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "draw.hpp"

using namespace cv;
using namespace std;

<<<<<<< Updated upstream
void symmetry(Image image, string filename);
void symmetryx(Image image, string filename);
double lowerfunc(Point point1, Point point2);
void weaken_pressure(Image image, Point center, int width, int height, double K);
=======
using namespace libfp::utils;

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
        void symmetryy(Image image);
        /*!
         *  \brief Symmetry/x
         *
         *  Performs a symmetry along the x axis on the given image
         *
         *  \param image : the image to modify
         */
        void symmetryx(Image image);
         /*!
          *  \brief Sigmoid
          *
          *  Returns the evaluation of the function used to simulate a weaken pressure
          *  in point2, given the center point1
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
         */
        void weaken_pressure(Image image, Point center, int width, int height, double K);

}
}

>>>>>>> Stashed changes

#endif
