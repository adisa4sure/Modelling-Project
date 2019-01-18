#include "./../include/utils.hpp"

Image::Image(string filename)
{
  stringstream ss;
  ss << "./images/" << filename << ".png";
  string link = ss.str();
  mat = imread(link, 0);
  width = mat.size().width;
  height = mat.size().height;
}

void Image::show(string windowname)
{
  namedWindow(windowname, WINDOW_AUTOSIZE);
  imshow(windowname, mat);
  waitKey(0);
}

Mat Image::getmat()  
{
  return mat;
}

void Image::setmat(Mat newmat)
{
  mat = newmat;
}

Size Image::getsize()
{
  return mat.size();
}

void savemat(Mat mat, string filename)
{
  stringstream ss;
  ss << "./images/" << filename << ".png";
  string link = ss.str();
  imwrite(link, mat);
  cout << "Image saved in the Modelling-project/images/   folder" << endl;
}

double distance(Point point1, Point point2)
{
  double dist = sqrt(pow(double(point1.x - point2.x),2) + pow(double(point1.y - point2.y), 2));
  return dist;
}

double theta(Point point1, Point point2)
{

}
