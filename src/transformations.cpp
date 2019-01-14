#include "./../include/transformations.hpp"

Image::symmetry(string filename, bool axis)
{ //axis = 0 --> y axis, axis = 1 --> x axis
  Mat modified_img(img.size(), CV_64FC1);
  vector<int> *> limits(2); //first value is the symmetry axs
  limits[int(axis)] = img.size().height;
  limits[int(!axis)] = img.size().width;
  for (int val1 = 0;val1 < limits[0]; val1++){
    for (int val2  = 0; val2 < limits[1]; val2++){
      Point point, point2;
      if(axis){
        point = Point(val1, val2);
        point2 = Point(limits[0] - val1, val2);
      } else {
        point = Point(val2, val1);
        point2 = Point(val2, limits[0] - val1)
      }
      modified_img.at<uchar>(point) = img.at<uchar>(point2)
    }
  }
  stringstream ss;
  ss << "./../images/" << filename << ".png";
  string link = ss.str();
  imwrite(link, modified_img);
  cout << "Image saved in the Modelling-project/images/ folder";
}
