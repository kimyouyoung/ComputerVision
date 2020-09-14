#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat lena, blur_lena;

    lena = imread("lena.png");
    imshow("lena", lena);

    Rect b_rect(0, 0, (int)(lena.cols/2), lena.rows);
    Rect rect((int)(lena.cols/2), 0, (int)(lena.cols/2), lena.rows);
    blur(lena, blur_lena, Size(7, 7));
    hconcat(blur_lena(b_rect), lena(rect), blur_lena);
    imshow("lena_filtered", blur_lena);

    Mat moon, sharp_moon;

    moon = imread("moon.png");
    imshow("moon", moon);

    Rect s_rect((int)(moon.cols/2), 0, (int)(moon.cols/2), moon.rows);
    Rect m_rect(0, 0, (int)(moon.cols/2), moon.rows);
    Laplacian(moon, sharp_moon, moon.type());
    // hconcat(moon(m_rect), sharp_moon(s_rect), sharp_moon);
    imshow("moon_filtered", sharp_moon);


    Mat saltnpepper, saltnpepper_filter;

    saltnpepper = imread("saltnpepper.png");
    imshow("saltnpepper", saltnpepper);

    medianBlur(saltnpepper, saltnpepper_filter, 9);
    imshow("saltnpepper_filtered", saltnpepper_filter);

    waitKey(0);

    return 0;
}