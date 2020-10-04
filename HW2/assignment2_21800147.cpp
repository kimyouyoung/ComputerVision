#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat gray_img, negative_img, log_img, gamma_img;

    gray_img = imread("lena.png", 0);

    negative_img = 255-gray_img;

    gray_img.convertTo(log_img,CV_32F);
    log_img = abs(log_img) + 1;
    log(log_img, log_img);
    log_img = 1.5f * log_img;
    normalize(log_img, log_img, 0, 255, NORM_MINMAX);
    convertScaleAbs(log_img, log_img); 

    // gray_img.convertTo(gamma_img, CV_32F);
    // gamma_img = gamma_img/255.0;
    // for(int i = 0; i < gamma_img.rows; i++){
    //     for(int j = 0; j < gamma_img.cols; j++){
    //         gamma_img.at<float>(i, j) = pow(gamma_img.at<float>(i, j), 0.5) * 255;
    //     }
    // }
    // gamma_img.convertTo(gamma_img, CV_8U);
    // gamma_img = gamma_img * 1;

    MatIterator_<uchar> it, end;
    float gamma = 0.5f;
    unsigned char pix[256];

    for(int i = 0; i < 256; i++){
        pix[i] = (uchar)(pow((float)(i / 255.0), gamma) * 255.0f);
    }

    gamma_img = gray_img.clone();

    for(it = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); it != end; it++){
        *it = pix[(*it)];
    }

    imshow("gray_img", gray_img);
    imshow("negative_img", negative_img);
    imshow("log_img", log_img);
    imshow("gamma_img", gamma_img);

    waitKey(0);
    return 0;
}