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

    Mat moon, sharp_moon;

    moon = imread("moon.png");
    imshow("moon", moon);

    Rect s_rect((int)(moon.cols/2), 0, (int)(moon.cols/2), moon.rows);
    sharp_moon = moon.clone();
    sharp_moon = sharp_moon(s_rect);
    Laplacian(sharp_moon, sharp_moon, CV_16S); 
    convertScaleAbs(sharp_moon, sharp_moon); 
    add(sharp_moon, moon(s_rect), sharp_moon);

    imshow("moon_filtered", moon);


    Mat saltnpepper, saltnpepper_filter;

    saltnpepper = imread("saltnpepper.png");
    imshow("saltnpepper", saltnpepper);

    medianBlur(saltnpepper, saltnpepper_filter, 9);
    imshow("saltnpepper_filtered", saltnpepper_filter);

    waitKey(0);

    return 0;
}