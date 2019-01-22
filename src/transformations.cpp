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
  savemat(modified_img, filename);
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

double lowerfunc(Point point1, Point point2, double K)
{
  //double result = 1/(1+exp(K*(distance(point1, point2)- 120)));
  double result = 1/(1+exp((K+K*abs(costheta(point1, point2)))*(distance(point1, point2) - 120 + abs(costheta(point1, point2)) * 50)));
  return result;
}


void weaken_pressure(Image image, Point center, int width, int height, double K)
{
  Mat immat = image.getmat();
  //for (int x = center.x - width/2; x < center.x + width/2 + 1; x++)
  for (int x = 0; x < image.getsize().width; x++)
  {
    //for (int y = center.y - height/2; y < center.y + height/2 + 1; y++)
    for (int y = 0; y < image.getsize().height; y++)
    {
      //immat.at<uchar>(Point(x,y)) = immat.at<uchar>(Point(x,y))*lowerfunc(center, Point(x,y), K);
      immat.at<uchar>(Point(x,y)) = 255 - double(255 - immat.at<uchar>(Point(x,y)))*lowerfunc(center, Point(x,y), K);
    }
  }
  image.setmat(immat);
}
