#include "transformations.hpp"

/*
Demo file for the main course 1 : weakening the pressure on a given fingerprint
*/

typedef std::function<void(int, int, int)> mouseCallback;

int main()
{
  Image cleanim("./images/clean_finger.png");
  int i = 1;
  bool stay = 1;
  double K;
  cleanim.show();
  mouseCallback fn1 = [&cleanim, &i, &stay, &K](int event, int x, int y) -> void {
          if(event != cv::EVENT_LBUTTONDOWN)
          {
                  return;
          } else {
                  libfp::transformations::weaken_pressure(cleanim, Point(x,y), 1, 1, K);
                  stay = 0;
          }
  };

  cleanim.registerCallback([](int event, int x, int y, int, void* callbackFunc) -> void {
          (*(mouseCallback*)callbackFunc)(event, x, y);
  }, (void*)&fn1);
  cout << "Enter the value of K, the parameter of the used function (see documentation to get more details) : " << endl;
  cin >> K;
  cout << "Click to select the center of the pressure weakening." << endl;
  while(stay)
  {
    cleanim.show();
    libfp::utils::waitKey(10);
  }
  cout << "Press a key to quit." << endl;

  cleanim.show();
  libfp::utils::waitKey(0);
}
