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

Mat colorSlicing(Mat src){
    Mat image, dst;
    Mat channels[3];

    cvtColor(src, image, CV_BGR2HSV);
    split(image, channels);

    for(int i = 0; i < channels[0].rows; i++){
        for(int j = 0; j < channels[0].cols; j++){
            if(channels[0].at<uchar>(i, j) <= 9 || channels[0].at<uchar>(i, j) >= 23)
                channels[1].at<uchar>(i, j) = 0;
        }
    }

    merge(channels, 3, dst);
    cvtColor(dst, image, CV_HSV2BGR);

    return image;
}

Mat colorConversion(Mat src){
    Mat image, dst;
    Mat channels[3];

    cvtColor(src, image, CV_BGR2HSV);
    split(image, channels);

    for(int i = 0; i < channels[0].rows; i++){
        for(int j = 0; j < channels[0].cols; j++){

            if(channels[0].at<uchar>(i, j) > 129)
                channels[0].at<uchar>(i, j) = channels[0].at<uchar>(i, j) - 129;
            else
                channels[0].at<uchar>(i, j)  += 50;
        }
    }

    merge(channels, 3, dst);
    cvtColor(dst, image, CV_HSV2BGR);

    return image;
}

Mat averageFilter(Mat src){
    Mat image;
    Mat channels[3];

    cvtColor(src, image, CV_BGR2HSV);
    split(image, channels);
    
    blur(channels[2], channels[2], Size(9, 9));

    erge(channels, 3, dst);
    cvtColor(dst, image, CV_HSV2BGR);

    return image;
}

Mat whiteBalancing(Mat src){
    Mat image;
    Mat channels[3];

    int b, g, r;

    split(src, channels);

    for(int i = 0; i < channels[0].rows; i++){
        for(int j = 0; j < channels[0].cols; j++){
            b += channels[0].at<uchar>(i, j);
            g += channels[1].at<uchar>(i, j);
            r += channels[2].at<uchar>(i, j);
        }
    }

    cout << b << endl;
    cout << g << endl;
    cout << r << endl;

    b = b / (channels[0].rows*channels[0].cols);
    g = g / (channels[0].rows*channels[0].cols);
    r = r / (channels[0].rows*channels[0].cols);

    

    int bb, gg, rr;
    for(int i = 0; i < channels[0].rows; i++){
        for(int j = 0; j < channels[0].cols; j++){
            channels[0].at<uchar>(i, j) *= (128 / b);
            channels[1].at<uchar>(i, j) *= (128 / g);
            channels[2].at<uchar>(i, j) *= (128 / r);

            bb += channels[0].at<uchar>(i, j);
            gg += channels[1].at<uchar>(i, j);
            rr += channels[2].at<uchar>(i, j);
        }
    }

    cout << bb / (channels[0].rows*channels[0].cols) << endl;
    cout << gg / (channels[0].rows*channels[0].cols) << endl;
    cout << rr / (channels[0].rows*channels[0].cols) << endl;

    merge(channels, 3, image);

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

        if(ch == 27)
            break;

        switch(ch){

            case 'n':{
                show_lena = negative(show_lena);
                cout << "Negative transformation" << endl;
                break;
            }

            case 'g':{
                show_lena = gamma(show_lena);
                cout << "Gamma transformation" << endl;
                break;
            }
            
            case 'h':{
                show_lena = histogram(show_lena);
                cout << "Histogram equalization" << endl;
                break;
            }

            case 's':{
                show_colorful = colorSlicing(show_colorful);
                cout << "Color slicing" << endl;
                break;
            }

            case 'c':{
                show_colorful = colorConversion(show_colorful);
                cout << "Color conversion" << endl;
                break;
            }

            case 'a':{
                show_balancing = averageFilter(show_balancing);
                cout << "Average filtering" << endl;
                break;
            }

            case 'w':{
                show_balancing = whiteBalancing(show_balancing);
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