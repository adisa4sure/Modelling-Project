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

void Image::show()
{
  namedWindow("Display", WINDOW_AUTOSIZE);
  imshow("Display", mat);
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
