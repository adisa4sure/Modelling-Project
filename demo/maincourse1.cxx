#include "transformations.hpp"

/*
Demo file for the main course 1 : weakening the pressure on a given fingerprint
*/

typedef std::function<void(int, int, int)> mouseCallback;

int main()
{
  Image weak_fp("./images/weak_finger.png");
  Mat black(Size(300, 300), CV_8U, Scalar(0));
  Image blackim(black);
  int i = 1;
  blackim.show("ZBRE");
  mouseCallback fn1 = [&blackim, &i](int event, int x, int y) -> void {
          if(event != cv::EVENT_LBUTTONDOWN)
          {
                  cout << "error" << endl;
                  return;
          } else {
          cout << "CLICK" << endl;
          }
  };
  blackim.registerCallback([](int event, int x, int y, int, void* callbackFunc) -> void {
          (*(mouseCallback*)callbackFunc)(event, x, y);
  }, (void*)&fn1);
  while(i){
  libfp::utils::waitKey(10);
  }
}
