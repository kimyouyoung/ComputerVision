#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat lena, blur_lena;

    lena = imread("lena.png");
    imshow("lena", lena);

    blur_lena = lena.clone();
    Rect b_rect(0, 0, (int)(lena.cols/2), lena.rows);
    blur(blur_lena(b_rect), blur_lena(b_rect), Size(7, 7));
    imshow("lena_filtered", blur_lena);

    Mat moon, p_moon, sharp_moon;

    moon = imread("moon.png");
    imshow("moon", moon);

    Laplacian(moon, sharp_moon, CV_16S); 
    convertScaleAbs(sharp_moon, sharp_moon); 
    add(sharp_moon, moon, sharp_moon);

    for(int i = 0; i <= moon.rows; i++){
        for(int j = 0; j <= moon.cols/2; j++){
            sharp_moon.at<uchar>(i, j) = moon.at<uchar>(i, j);
        }
    }
    imshow("moon_filtered", sharp_moon);


    Mat saltnpepper, saltnpepper_filter;

    saltnpepper = imread("saltnpepper.png");
    imshow("saltnpepper", saltnpepper);

    medianBlur(saltnpepper, saltnpepper_filter, 9);
    imshow("saltnpepper_filtered", saltnpepper_filter);

    waitKey(0);

    return 0;
}