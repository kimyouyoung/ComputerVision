#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat negative(Mat src){
    Mat image, dst;
    Mat channels[3];

    cvtColor(src, image, CV_BGR2HSV);
    split(image, channels);
   
    for(int i = 0; i < channels[2].rows; i++){
        for(int j = 0; j < channels[2].cols; j++){
            channels[2].at<uchar>(i, j) = 255 - 1 - channels[2].at<uchar>(i, j);
        }
    }

    merge(channels, 3, dst);
    cvtColor(dst, image, CV_HSV2BGR);

    return image;
}

Mat gamma(Mat src){
    Mat image, dst;
    Mat channels[3];

    cvtColor(src, image, CV_BGR2HSV);
    split(image, channels);

    channels[2].convertTo(channels[2], CV_32F);
    channels[2] = channels[2]/255.0;
    for(int i = 0; i < channels[2].rows; i++){
        for(int j = 0; j < channels[2].cols; j++){
            channels[2].at<float>(i, j) = pow(channels[2].at<float>(i, j), 2.5) * 255;
        }
    }
    channels[2].convertTo(channels[2], CV_8U);
    merge(channels, 3, dst);
    cvtColor(dst, image, CV_HSV2BGR);

    return image;
}

Mat histogram(Mat src){
    Mat image, dst;
    Mat channels[3];

    cvtColor(src, image, CV_BGR2HSV);
    split(image, channels);

    equalizeHist(channels[2], channels[2]);

    merge(channels, 3, dst);
    cvtColor(dst, image, CV_HSV2BGR);

    return image;
}

Mat averageFilter(Mat src){
    Mat image;

    blur(src, image, Size(9, 9));

    return image;
}


int main(){

    char ch;

    Mat lena, colorful, balancing;
    lena = imread("lena.png");
    colorful = imread("colorful.jpg");
    balancing = imread("balancing.jpg");

    Mat show_lena, show_colorful, show_balancing;
    show_lena = lena;
    show_colorful = colorful;
    show_balancing = balancing;

    while(1){

        switch(ch){

            case 'n':{
                show_lena = negative(lena);
                cout << "Negative transformation" << endl;
                break;
            }

            case 'g':{
                show_lena = gamma(lena);
                cout << "Gamma transformation" << endl;
                break;
            }
            
            case 'h':{
                show_lena = histogram(lena);
                cout << "Histogram equalization" << endl;
                break;
            }

            case 's':{
                Mat slicing;
                show_colorful = slicing;
                cout << "Color slicing" << endl;
                break;
            }

            case 'c':{
                Mat conversion;
                cvtColor(colorful, conversion, CV_BGR2YUV);
                show_colorful = conversion;
                cout << "Color conversion" << endl;
                break;
            }

            case 'a':{
                show_balancing = averageFilter(balancing);
                cout << "Average filtering" << endl;
                break;
            }

            case 'w':{
                Mat white_b;
                show_balancing = white_b;
                cout << "White balancing" << endl;
                break;
            }

            case 'r':{
                show_lena = lena;
                show_colorful = colorful;
                show_balancing = balancing;
                cout << "Reset" << endl;
                break;
            }
        }

        imshow("lena", show_lena);
        imshow("colorful", show_colorful);
        imshow("balancing", show_balancing);

        ch = waitKey(1000);
    }

    return 0;
}