#include "transformations.hpp"

/*
Demo file for the main course 1 : weakening the pressure on a given fingerprint
*/

typedef std::function<void(int, int, int)> mouseCallback;

int main()
{
  Image image("./images/cleanfingcap.png"); //Opens the clean finger image
  Image clean("./images/cleanfingcap.png");
  Image weakcap("./images/weakfingcap.png");
  Kernel ker(5,1,1, "Plus");
  bool stay = 1;   //Initializing the variable used to know when the user has clicked
  double K; //Initializing the parametre variable
  int s;
  image.show();
  //Function called when the user clicks on the image
  //The position of the pointer is given in parameter and used as the center
  mouseCallback fn1 = [&image, &stay, &K, &s, &ker](int event, int x, int y) -> void {
          if(event != cv::EVENT_LBUTTONDOWN)
          {
                  return;
          } else {
                  libfp::transformations::gray_erosion(image, ker);
                  libfp::transformations::weaken_pressure(image, Point(x,y), 1, 1, K, s); //Performing the pressure weakening
                  stay = 0; //Putting the variable to 0 to stop the loop
          }
  };

  image.registerCallback([](int event, int x, int y, int, void* callbackFunc) -> void {
          (*(mouseCallback*)callbackFunc)(event, x, y);
  }, (void*)&fn1); //Binds the function to a mouse event on the image
  cout << "Enter the value of K, the parameter of the used function (see documentation to get more details) : " << endl;
  cin >> K; //Takes the input as parameter
  cout << "Enter the valule of s, tuning the size of the weakened fingerprint (see documentation to get more details) : " << endl;
  cin >> s;
  cout << "Click to select the center of the pressure weakening." << endl;
  //Waits for a click
  while(stay)
  {
    image.show();
    libfp::utils::waitKey(10);
  }
  cout << "Press a key to quit." << endl;
  imshow("Result", image.getmat());
  imshow("Clean finger", clean.getmat());
  imshow("Weak finger", weakcap.getmat());
  libfp::utils::waitKey(0);
}
