#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    Mat finger, adaptive_1, adaptive;
    finger = imread("Finger.png", 0);
    adaptive_1 = imread("adaptive_1.jpg", 0);
    adaptive = imread("adaptive.png", 0);

    threshold(finger, finger, 0, 255, THRESH_BINARY | THRESH_OTSU);

    adaptiveThreshold(adaptive_1, adaptive_1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 19, 10);
    
    adaptiveThreshold(adaptive, adaptive, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 10);
    
    imshow("finger_print", finger);
    imshow("adaptive_1", adaptive_1);
    imshow("adaptive", adaptive);

    waitKey(0);
    return 0;
}