#include "transformations.hpp"

/*
Demo file for the main course 1 : weakening the pressure on a given fingerprint
*/

typedef std::function<void(int, int, int)> mouseCallback;

int main()
{
  Image image("./images/clean_finger.png"); //Opens the clean finger image
  Image image2("./images/clean_finger.png");
  Image clean("./images/clean_finger.png");
  Kernel ker(3,1,1, "Plus");
  bool stay = 1;   //Initializing the variable used to know when the user has clicked
  double K; //Initializing the parametre variable
  int s;
  image.show();
  //Function called when the user clicks on the image
  //The position of the pointer is given in parameter and used as the center
  mouseCallback fn1 = [&image, &stay, &K, &s, &image2, &ker](int event, int x, int y) -> void {
          if(event != cv::EVENT_LBUTTONDOWN)
          {
                  return;
          } else {
                  libfp::transformations::weaken_pressure(image, Point(x,y), 1, 1, K, s); //Performing the pressure weakening
                  stay = 0; //Putting the variable to 0 to stop the loop
          }
  };

  image.registerCallback([](int event, int x, int y, int, void* callbackFunc) -> void {
          (*(mouseCallback*)callbackFunc)(event, x, y);
  }, (void*)&fn1); //Binds the function to a mouse event on the image
  cout << "Enter the value of K, tuning the steepness of the function (see documentation to get more details) : " << endl;
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
  imshow("Weaker pressure", image.getmat());
  imshow("Weaker pressure + erosion", image2.getmat());
  imshow("Clean finger", clean.getmat());
  libfp::utils::waitKey(0);
}
