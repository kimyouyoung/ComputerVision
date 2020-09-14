#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat gray_img, negative_img, log_img, gamma_img;

    gray_img = imread("lena.png", 0);

    negative_img = 255-1-gray_img;

    gray_img.convertTo(f_img,CV_32F);
    f_img = abs(f_img) + 1;
    log(f_img, f_img);
    f_img = 1.5f * f_img;
    normalize(f_img, f_img, 0, 255, NORM_MINMAX);
    // log_img.convertTo(log_img, CV_8U); 
    convertScaleAbs(f_img, log_img); 
    
    Matlterator_<uchar> it, end;
    float gamma = 0.5f;
    unsigned char pix[256];

    for(int i = 0; i < 256; i++){
        pix[i] = (uchar)(pow(float)(i/255.0))
    }
    gray_img.convertTo(gamma_img, CV_32F);
    gamma_img = gamma_img/255.0;
    for(int i = 0; i < gamma_img.rows; i++){
        for(int j = 0; j < gamma_img.cols; j++){
            gamma_img.at<float>(i, j) = pow(gamma_img.at<float>(i, j), 0.5);
        }
    }
    gamma_img.convertTo(gamma_img, CV_8U, 255);
    gamma_img = gamma_img * 1;

    imshow("gray_img", gray_img);
    imshow("negative_img", negative_img);
    imshow("log_img", log_img);
    imshow("gamma_img", gamma_img);

    waitKey(0);
    return 0;
}