#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat gray_img, negative_img, log_img, gamma_img;

    gray_img = imread("lena.png", 0);

    negative_img = 255-1-gray_img;

    gray_img.convertTo(log_img,CV_32F);
    log_img = 1 + log_img;
    log(log_img, log_img);
    normalize(log_img, log_img, 0, 255, NORM_MINMAX);
    log_img.convertTo(log_img, CV_8U); 
    log_img = log_img * 1.5;
    

    gray_img.convertTo(gamma_img, CV_32F);
    normalize(gamma_img, gamma_img, 0, 1.0, NORM_MINMAX);
    pow(gamma_img, 0.5, gamma_img);
    normalize(gamma_img, gamma_img, 0, 255, NORM_MINMAX);
    gamma_img.convertTo(gamma_img, CV_8U); 
    gamma_img = gamma_img * 1.1;

    imshow("gray_img", gray_img);
    imshow("negative_img", negative_img);
    imshow("log_img", log_img);
    imshow("gamma_img", gamma_img);

    waitKey(0);
    return 0;
}