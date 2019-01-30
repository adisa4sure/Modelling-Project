#include "transformations.hpp"

int main(){
    Image image("./images/clean_finger.png");
    Kernel kernel(3, 1, 1, "Square");
    Image test = erosion(image, kernel, 127);
    test.show();
    return(0);
}
