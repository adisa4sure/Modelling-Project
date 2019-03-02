#ifndef UTILS_H
#define UTILS_H

#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

namespace libfp{
namespace utils{
        void waitKey(int);
        /*!
         *  \brief Saves an image
         *
         *  Saves the image contained in mat to a new file
         *
         *  \param mat : the Mat to save in a new file
         *  \param filename : the path+filename in which we save the image
         */
        void savemat(Mat mat, string filename);

        /*!
         *  \brief Distance
         *
         *  Returns the distance between the two points given as parameters
         *
         *  \param point1 : first point of the segment
         *  \param point2 : second point of the segment
         */
        double distance(Point point1, Point point2);

        /*!
         *  \brief Cos(theta)
         *
         *  Returns the cos of the angle between the vectors (point1, point2) and (point1, Point(point1.x + K,point1.y))
         *
         *  \param point1 : center of the circle
         *  \param point2 : point of computation
         */
        double costheta(Point point1, Point point2);

        /*!
         *  \brief Parity
         *
         *  Returns 1 if x is odd, 0 if it is even
         *
         *  \param x : number
         */
        bool parity(unsigned  int x);
        /*!
           *  \brief Constructeur
           *
           *  Constructeur de la classe CPlayer
           *
           *  \param listSongs : liste initial des morceaux
           */
        Mat fourier(Mat);
        Mat gaus_ker(int size);
        Mat fill_ker(Mat, Size);
        void shift(Mat);
}
}

/*! \class Image
 * \brief Class containing the image
 *  This class contains the image's Mat (a matrix corresponding to the image),
 *  a few other characteristics like the width and height, and methods to
 *  allow interaction with the image
 *
 */

class Image
{
private:
  Mat mat; /*!< Matrix of type Mat (from opencv) that contains the intensities of the grayscale image*/
  int height; /*!< Height of the image in pixels*/
  int width; /*!< Width of the image in pixels*/
  string window_name; /*!< Text displayed as the window name when the image is shown*/
public:
  /*!
     *  \brief Constructeur
     *
     *  Constructor of the Image class from a file
     *
     *  \param filename : string containing the path to the image to open
     */
  Image(string filename);
  /*!
     *  \brief Constructeur
     *
     *  Constructor of the Image class from a Mat
     *
     *  \param cmat : Mat set as the image
     *  \param name : string used for the window name
     */
  Image(Mat cmat, string name);
  /*!
     *  \brief Display
     *
     *  Displays the image in a new window
     *
     *  \param force_window_name : name of the window if we don't wan't to use the window_name attribute
     */
  void show(string force_window_name = "");
  /*!
     *  \brief Getter
     *
     *  Returns the Mat of the image
     */
  Mat getmat() const;
  /*!
     *  \brief Setter
     *
     *  Modifies the Mat
     *
     *  \param newmat : new Mat to use for the image
     */
  void setmat(Mat newmat);
  /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe CPlayer
     *
     *  \param listSongs : liste initial des morceaux
     */
  Size getsize() const;
  /*!
     *  \brief Convolution
     *
     *  Convolves the image's matrix with the one given in parameter
     *
     *  \param filter : kernel
     *  \param half : only modifies half of the image if it is True
     */
  void convolve(Mat_<double> filter, bool half = 0);
  /*!
     *  \brief Links callback
     *
     *  Links a
     *
     *  \param callback :
     */
  void registerCallback(MouseCallback callback, void* userdata = 0);
  /*!
     *  \brief Clone
     *
     *  Returns a copy of the Image
     *
     */
  Image clone();
  /*!
     *  \brief Applies noise
     *
     *  Merges the image with the noise given in parameter
     *
     *  \param noiseim : noise Image used for the merge
     */
  void apply_noise(Image& noiseim);
  /*!
     *  \brief Binarize the image
     *
     *  Convert the values of the image's matrix in 0 or 1 depending on if there are above
     *  or below a certain value (threshold).
     *
     *  \param threshold : value used as threshold
     */
  void binarization(int threshold);
  /*!
     *  \brief Convert a binarized image
     *
     *  Convert a binarized image to a black and white image.
     *
     */
  void grayscale();
};


/*! \class Kernel
 * \brief Class containing the kernel/mask used to filter an image
 *  This class contains the kernel's Mat (a matrix corresponding to shape of the mask),
 *  a few other characteristics like the dimension of this matrix, an origin point,
 *  and methods to apply this filter to an image
 *
 */
 class Kernel{
     private:
         cv::Mat mask; /*!< Matrix of type Mat (from opencv) that contains the shape of the kernel*/
         int dim;  /*!< Dimension of the matrix Mat (height = width)*/
         int x_ori; /*!< Abscissa of the origin point*/
         int y_ori;  /*!< Ordinate of the origin point*/
     public:
         /*!
            *  \brief Constructor
            *
            *  Constructor of the Kernel class
            *
            *  \param dim : dimension of the matrix Mat
            *  \param x : abscissa of the origin point
            *  \param y : ordnate of the origin point
            *  \param type : indicate the shape of the kernel : "Square" or "Plus"
            */
         Kernel(int dim, int x, int y, std::string type);
         /*!
            *  \brief Getter
            *
            *  Returns the Mat of the kernel
            */
         cv::Mat getmask() const;
         /*!
            *  \brief Getter
            *
            *  Returns the dimension of the kernel's matrix
            */
         int getdim() const;
         /*!
            *  \brief Getter
            *
            *  Returns the origin point of the kernel's matrix
            */
         cv::Point getorig() const;
         /*!
            *  \brief Erosion operation
            *
            *  Returns the value of the image's pixel corresponding
            *  to the kernel's origin after erosion.
            *  This method only works for black and white images.
            *
            *  \param image : matrix on which the filter is applied
            */
         int erode(cv::Mat image);
         /*!
            *  \brief Dilatation operation
            *
            *  Returns the value of the image's pixel corresponding
            *  to the kernel's origin after dilatation.
            *  This method only works for black and white images.
            *
            *  \param image : matrix on which the filter is applied
            */
         int dilate(cv::Mat image);
         /*!
            *  \brief Erosion operation
            *
            *  Returns the value of the image's pixel corresponding
            *  to the kernel's origin after erosion.
            *  Works for grayscale images.
            *
            *  \param image : matrix on which the filter is applied
            */
         int erode_gray(Mat image);
         /*!
            *  \brief Dilatation operation
            *
            *  Returns the value of the image's pixel corresponding
            *  to the kernel's origin after dilation.
            *  Works for grayscale images.
            *
            *  \param image : matrix on which the filter is applied
            */
         int dilate_gray(Mat image);

 };

#endif
