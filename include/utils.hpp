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
     *  Constructor of the Image class
     *
     *  \param filename : string containing the path to the image to open
     */
  Image(string filename);
  /*!
     *  \brief Constructeur
     *
     *  Constructor of the Image class
     *
     *  \param filename : string containing the path to the image to open
     */
  Image(Mat cmat, string);
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
     *  \brief Constructeur
     *
     *  Constructeur de la classe CPlayer
     *
     *  \param listSongs : liste initial des morceaux
     */
  void registerCallback(MouseCallback callback, void* userdata = 0);
  /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe CPlayer
     *
     *  \param listSongs : liste initial des morceaux
     */
  Image clone();
};

#endif
