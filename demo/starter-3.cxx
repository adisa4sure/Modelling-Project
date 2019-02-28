#include "transformations.hpp"
#include <chrono>
#include <fstream>

void benchmark(Image& image, Image& image2, Image& clean)
{
  ofstream file;
  file.open("data.csv", ofstream::out | ofstream::trunc); //Opens the data.csv file an d empties it
  file << "i, elapsedf, elapsedc\n"; //Sets the column names
  chrono::high_resolution_clock::time_point beginningf, endf, beginningc, endc; //Initializes the time variables
  chrono::duration<double> elapsedf, elapsedc; //Initializes the duration variable
  for(int i = 1; i < 30; i++)
  {
    //Performs the Fourier convolution and measures the computing time
    beginningf = chrono::high_resolution_clock::now();
    libfp::transformations::blur_fc(image, (2*i)+1);
    endf = chrono::high_resolution_clock::now();
    elapsedf = endf - beginningf;

    //Performs the greedy convolution and measures the computing time
    beginningc = chrono::high_resolution_clock::now();
    libfp::transformations::blur_gc(image2, (2*i)+1);
    endc = chrono::high_resolution_clock::now();
    elapsedc = endc - beginningc;

    file << i << "," << elapsedf.count() << "," << elapsedc.count() << "\n"; //Writes the measured times in the csv file

    //Resets the images
    image = clean.clone();
    image2 = clean.clone();
  }
  file.close(); //Closes the file
}




int main()
{
  //Opening the images we work on
  Image image("./images/clean_finger.png");
  Image image2("./images/clean_finger.png");
  Image clean("./images/clean_finger.png");

  //Decomment to run benchmark the function : saves the results in the file data.csv
  //benchmark(image, image2, clean);

  namedWindow("Difference between reults");
  namedWindow("Fourier, kernel 3x3");
  namedWindow("Greedy convolution, kernel 3x3");

  //Blurs the image with the Fourier convolution method and measures its computing time
  auto beginningf = chrono::high_resolution_clock::now();
  libfp::transformations::blur_fc(image, 5);
  auto endf = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsedf = endf - beginningf;

  //Blurs the image with the greedy convolution method and measures its computing time
  auto beginningc = chrono::high_resolution_clock::now();
  libfp::transformations::blur_gc(image2, 5);
  auto endc = chrono::high_resolution_clock::now();
  chrono::duration<double> elapsedc = endc - beginningc;

  cout << "Fourier convolution time : " << elapsedf.count() << "seconds." << endl;
  cout << "Greedy convolution time : " << elapsedc.count() << "seconds." << endl;

  Image difference(cv::abs(clean.getmat()-image2.getmat()), "DIFF"); // Creates the image showing the difference between the two resutls
  libfp::transformations::negative(difference); // Put in negative to visualize it better

  imshow("Greedy convolution, kernel 3x3", image2.getmat());
  imshow("Clean", clean.getmat());
  imshow("Fourier, kernel 3x3", image.getmat());
  imshow("Difference between results", difference.getmat());

  libfp::utils::waitKey(0);
}
