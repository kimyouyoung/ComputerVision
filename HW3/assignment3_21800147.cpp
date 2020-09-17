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

    moon = imread("moon.jpg");
    imshow("moon", moon);
 
    Mat output = Mat::zeros(moon.size(), moon.type());

    for(int i = 0; i < moon.rows; i++){
        for(int j = 0; j < moon.cols/2; j++){
            output.at<Vec3b>(i, j) = moon.at<Vec3b>(i, j);
        }
    }

    Laplacian(moon, sharp_moon, CV_16S);
    convertScaleAbs(sharp_moon, sharp_moon);
    add(sharp_moon, moon, sharp_moon);

    for(int i = 0; i < moon.rows; i++){
        for(int j = moon.cols/2; j < moon.cols; j++){
            output.at<Vec3b>(i, j) = sharp_moon.at<Vec3b>(i, j);
        }
    }

    imshow("moon_filtered", output);


    Mat saltnpepper, saltnpepper_filter;

    saltnpepper = imread("saltnpepper.png");
    imshow("saltnpepper", saltnpepper);

    medianBlur(saltnpepper, saltnpepper_filter, 9);
    imshow("saltnpepper_filtered", saltnpepper_filter);

    waitKey(0);

    return 0;
}