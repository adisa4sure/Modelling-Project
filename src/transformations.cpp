#include "./../include/draw.hpp"

void symmetryy(Image image, string filename)
{ //axis = 0 --> y axis, axis = 1 --> x axis
  Mat imagemat = image.getmat();
  Size taille = image.getsize();
  Mat modified_img(taille, CV_8U);
  for (int x = 0; x < taille.width; x++){
    for (int y = 0; y < taille.height;y++){
      modified_img.at<uchar>(Point(x,y)) = imagemat.at<uchar>(Point(taille.width-1-x,y));
    }
  }
  savemat(modified_img, filename)
}

void symmetryx(Image image, string filename)
{ //axis = 0 --> y axis, axis = 1 --> x axis
  Mat imagemat = image.getmat();
  Size taille = image.getsize();
  Mat modified_img(taille, CV_8U);
  for (int x = 0; x < taille.width; x++){
    for (int y = 0; y < taille.height;y++){
      modified_img.at<uchar>(Point(x,y)) = imagemat.at<uchar>(Point(x, taille.height-1-y));
    }
  }
  savemat(modified_img, filename);
}
