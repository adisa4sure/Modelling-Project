#include "./../include/utils.hpp"
#include <cstdlib>
#include <ctime>


namespace libfp{
    namespace utils{
        int waitKey(int ms){
            return cv::waitKey(ms);
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

    namedWindow(window_name, WINDOW_AUTOSIZE);
}

Image Image::clone()
{
    Image ret = Image(*this);
    ret.mat = mat.clone();
    ret.window_name = window_name + "_copy" + to_string(rand() % 1000);

    namedWindow(ret.window_name, WINDOW_AUTOSIZE);

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

void Image::convolve(Mat filter, bool half)
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
    int noperations = (imax+1-px)*(s.height-2*py)*(2*px+1)*(2*py+1);
    int count = 0;
    double sum;
    double add;
    cout << "Matrice : " << filter << endl;
    cout<<"Number of operations : "<<noperations<<endl;
    for (int i = px; i < imax+1; i++)
    {
        for (int j = py; j < s.height-py; j++)
        {
            sum = 0;
            for (int k = -px; k < px+1; k++)
            {
                for (int l = -py; l < py+1; l++)
                {
                    count++;
                    //cout << "coordinates" << Point(k+px, l+py) << endl;
                    //cout << "Intensity : " <<  intens << "\nFilter value : " << filter_val << endl;
                    //sum += mat.at<uchar>(j+l,i+k)*(filter.at<uchar>(l+py,k+px)/256);
                    add = double(mat.at<uchar>(j+l,i+k))*(double(filter.at<uchar>(l+py,k+px))/256);
                    sum += add;
                    //cout << "Adding : " << add << endl;
                    system("clear");
                    cout << count << "/" << noperations << endl;
                    //cout << "Adding : " << mat.at<uchar>(j+l,i+k)*filter.at<uchar>(l+py,k+px) << "\nSum = " << sum << endl;
                }
            }
            //cout << "Value pixel (" << i << "," << j << ") : " << sum << endl;
            output.at<uchar>(j,i) = sum;
            //cout << "SUm value : " << sum << endl;
        }
    }
    mat = output;
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
