#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
        if(argc != 2)
        {
                cout << "Usage: " << argv[0] << " [Image to load]" << endl;
                return -1;
        }

        Mat image = imread(argv[1], IMREAD_COLOR);

        if(image.empty())
        {
                cout << "Could not load image " << argv[1] << endl;
                return -1;
        }

        namedWindow("View", WINDOW_AUTOSIZE);
        imshow("View", image);
        waitKey(0);
        return 0;
}
