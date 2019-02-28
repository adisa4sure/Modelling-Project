#include "./../include/utils.hpp"
#include <cstdlib>
#include <ctime>
#define SIGMA_CLIP 6.0f

namespace libfp{
namespace utils{
        void waitKey(int ms){
                cv::waitKey(ms);
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

        double costheta(Point point1, Point point2)
        {
          if (point1.x == point2.x) {return 0;}
          double dotp = pow((point2.x - point1.x),2);
          double normp = distance(point1, point2)*distance(point1, Point(point2.x, point1.y));
          return(dotp/normp);
        }

        bool parity(unsigned int x){
            if (x%2 == 0){
              return 0;
            } else {
              return 1;
            }
        }

        Mat fourier(Mat input)
        {
          Mat ff_in, ff_out;
          input.convertTo(ff_in, CV_32FC1, 1.0/255.0);
          dft(ff_in, ff_out, DFT_COMPLEX_OUTPUT );
          return(ff_out);
        }
        Mat gaus_ker(int size)
        {
          double sigma = (size/SIGMA_CLIP + 0.5f);
          Mat_<double> kernelX = getGaussianKernel(2*size+1, sigma, CV_32FC1);
          Mat_<double> kernelY = getGaussianKernel(2*size+1, sigma, CV_32FC1);
          Mat_<double> kernel = kernelX * kernelY.t();
          return kernel;
        }

        Mat fill_ker(Mat kernel, Size imsize)
        {
            int r = (imsize.width - kernel.cols)/2;
            int l = imsize.width - kernel.cols - r;
            int b = (imsize.height - kernel.rows)/2;
            int t = imsize.height - kernel.rows - b;
            Mat result;
            copyMakeBorder(kernel, result,t,b,l,r, BORDER_CONSTANT, Scalar::all(0));
            return result;
        }
        //FUNCTION FOUND ON THE INTERNET (stackoverflow)
        void shift(Mat magI) {

            // crop if it has an odd number of rows or columns
            magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

            int cx = magI.cols/2;
            int cy = magI.rows/2;

            Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
            Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
            Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
            Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

            Mat tmp;                            // swap quadrants (Top-Left with Bottom-Right)
            q0.copyTo(tmp);
            q3.copyTo(q0);
            tmp.copyTo(q3);
            q1.copyTo(tmp);                     // swap quadrant (Top-Right with Bottom-Left)
            q2.copyTo(q1);
            tmp.copyTo(q2);
        }
}
}

static bool randseed = false;

Image::Image(string filename)
{
    mat = imread(filename, 0);

    if(!randseed){
        srand(time(NULL));
        randseed = true;
    }

    window_name = filename + to_string(rand() % 1000);
    width = mat.size().width;
    height = mat.size().height;

    //namedWindow(window_name, WINDOW_AUTOSIZE);
}

Image::Image(Mat cmat, string wname)
{
  mat = cmat.clone();
  width = mat.size().width;
  height = mat.size().height;
  window_name = wname;
}

Image Image::clone()
{
    Image ret = Image(*this);
    ret.mat = mat.clone();
    ret.window_name = window_name + "_copy" + to_string(rand() % 1000);
    //namedWindow(ret.window_name, WINDOW_AUTOSIZE);
    return ret;
}


void Image::show(string force_window_name)
{
    if(!force_window_name.length()){
        imshow(window_name, mat);
    }else{
        imshow(force_window_name, mat);
    }
}

void Image::registerCallback(MouseCallback callback, void* userdata){
    setMouseCallback(window_name, callback, userdata);
}

Mat Image::getmat() const
{
    return mat;
}

void Image::setmat(Mat newmat)
{
    mat = newmat;
}

Size Image::getsize() const
{
    return mat.size();
}

void Image::apply_noise(Image noise)
{
  
}

void Image::convolve(Mat_<double> filter, bool half)
{
  Size s = mat.size();
  int px = (filter.size().width-1)/2;
  int py = (filter.size().height-1)/2;
  Mat output = mat.clone();
  int imax;
  if (half)
  {
    imax = s.width/2;
  } else
  {
    imax = s.width - px;
  }
  double sum;
  for (int i = px; i < imax+1; i++)
  {
    for (int j = py; j < s.height-py; j++)
    {
      sum = 0;
      for (int k = -px; k < px+1; k++)
      {
        for (int l = -py; l < py+1; l++)
        {
          sum += (double)mat.at<uchar>(j+l,i+k)*((double)filter.at<double>(l+py,k+px));
        }
      }
      output.at<uchar>(j,i) = int(sum);
    }
  }
  mat = output;
}

void Image::binarization(int threshold){
    if(threshold < 0 || threshold > 255){
        cout << "threshold not in range 0-255";
        std::exit(EXIT_FAILURE);
    }
    int x = this -> width;
    int y = this -> height;
    for(unsigned int i = 0; i < x; i++){
        for(unsigned int j = 0; j < y; j++){
            if(mat.at<uchar>(j,i) <= threshold){
                mat.at<uchar>(j,i) = 0;
            }
            else{
                mat.at<uchar>(j,i) = 1;
            }
        }
    }
}

void Image::grayscale(){
    int x = this -> width;
    int y = this -> height;
    for(unsigned int i = 0; i < x; i++){
        for(unsigned int j = 0; j < y; j++){
            mat.at<uchar>(j,i) *= 255;
        }
    }
}

Kernel::Kernel(int dim, int x, int y, std::string type){
    if (x < 0 || dim <= x || y < 0 || dim <= y){
        cout << "Wrong origin values - default set to (0,0)";
        x_ori = 0;
        y_ori = 0;
    }
    this -> dim = dim;
    this -> x_ori = x;
    this -> y_ori = y;
    if(std::string("Square").compare(type) == 0){
        mask = Mat::ones(dim, dim, CV_8U);
    }
    else if(std::string("Plus").compare(type) == 0){
        if (dim%2 != 1){
            cout << "Wrong dimension for this kind of kernel - Enter an odd one" << endl;
            cout << "Default set to square" << endl;
            mask = Mat::ones(dim, dim, CV_8U);
        } else {
            mask = Mat::zeros(dim, dim, CV_8U);
            int center = dim/2;
            for(unsigned int i = 0; i < dim; i++){
                mask.at<uchar>(center, i) = 1;
                mask.at<uchar>(i, center) = 1;
            }
        }
    }
    else {
        cout << "Unknown type for kernel - Default set to square" << endl;
        mask = Mat::ones(dim, dim, CV_8U);
    }
}

Mat Kernel::getmask() const {
    return mask;
}

int Kernel::getdim() const {
    return dim;
}

Point Kernel::getorig() const {
    return Point(x_ori, y_ori);
}

int Kernel::erode(Mat image){
    if(mask.size() != image.size()){
        cout << "Wrong dimension in the matrix";
        return image.at<uchar>(y_ori, x_ori);
    }
    for(unsigned int i = 0; i < dim; i++){
        for(unsigned int j = 0; j < dim; j++){
            if(mask.at<uchar>(j,i) == 1 && image.at<uchar>(j,i) != 0){
                return 1;
            }
        }
    }
    return 0;
}

int Kernel::dilate(Mat image){
    if(mask.size() != image.size()){
        cout << "Wrong dimension in the matrix";
        return image.at<uchar>(y_ori, x_ori);
    }
    for(unsigned int i = 0; i < dim; i++){
        for(unsigned int j = 0; j < dim; j++){
            if(mask.at<uchar>(j,i) == 1 && image.at<uchar>(j,i) == 0){
                return 0;
            }
        }
    }
    return 1;
}

int Kernel::dilate_gray(Mat image){
    if(mask.size() != image.size()){
        cout << "Wrong dimension in the matrix";
        return image.at<uchar>(y_ori, x_ori);
    }
    int min = 255;
    for(unsigned int i = 0; i < dim; i++){
        for(unsigned int j = 0; j < dim; j++){
            if(mask.at<uchar>(j,i) == 1 && image.at<uchar>(j,i) < min){
                min = image.at<uchar>(j,i);
            }
        }
    }
    return min;
}

int Kernel::erode_gray(Mat image){
    if(mask.size() != image.size()){
        cout << "Wrong dimension in the matrix";
        return image.at<uchar>(y_ori, x_ori);
    }
    int max = 0;
    for(unsigned int i = 0; i < dim; i++){
        for(unsigned int j = 0; j < dim; j++){
            if(mask.at<uchar>(j,i) == 1 && image.at<uchar>(j,i) > max){
                max = image.at<uchar>(j,i);
            }
        }
    }
    return max;
}
