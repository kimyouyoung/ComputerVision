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
            channels[2].at<uchar>(i, j) = 255 - channels[2].at<uchar>(i, j);
            if(channels[2].at<uchar>(i, j) > 255)
                channels[2].at<uchar>(i, j) = 255;
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

    MatIterator_<uchar> it, end;
    float gamma = 2.5f;
    unsigned char pix[256];

    for(int i = 0; i < 256; i++){
        pix[i] = (uchar)(pow((float)(i / 255.0), gamma) * 255.0f);
    }

    for(it = channels[2].begin<uchar>(), end = channels[2].end<uchar>(); it != end; it++){
        *it = pix[(*it)];
    }

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
    Mat image, dst;
    Mat channels[3];

    cvtColor(src, image, CV_BGR2HSV);
    split(image, channels);

    blur(channels[2], channels[2], Size(9, 9));

    merge(channels, 3, dst);
    cvtColor(dst, image, CV_HSV2BGR);

    return image;
}

Mat whiteBalancing(Mat src){
    Mat image;
    Mat channels[3];

    int blue = 0;
    int green = 0;
    int red = 0;

    split(src, channels);

    channels[0].convertTo(channels[0], CV_32F);
    channels[1].convertTo(channels[1], CV_32F);
    channels[2].convertTo(channels[2], CV_32F);

    for(int i = 0; i < channels[0].rows; i++){
        for(int j = 0; j < channels[0].cols; j++){
            blue += channels[0].at<float>(i, j);
            green += channels[1].at<float>(i, j);
            red += channels[2].at<float>(i, j);
        }
    }

    blue /= (channels[0].rows * channels[0].cols);
    green /= (channels[1].rows * channels[1].cols);
    red /= (channels[2].rows * channels[2].cols);

    for(int i = 0; i < channels[0].rows; i++){
        for(int j = 0; j < channels[0].cols; j++){
            channels[0].at<float>(i, j) = channels[0].at<float>(i, j) * 128 / blue;
            channels[1].at<float>(i, j) = channels[1].at<float>(i, j) * 128 / green;
            channels[2].at<float>(i, j) = channels[2].at<float>(i, j) * 128 / red;

             if(channels[0].at<float>(i, j) > 255){
                channels[0].at<float>(i, j) = 255;
             }else if(channels[1].at<float>(i, j) > 255){
                channels[1].at<float>(i, j) = 255;
             }else if(channels[2].at<float>(i, j) > 255){
                channels[2].at<float>(i, j) = 255;
             }

        }
    }

    channels[0].convertTo(channels[0], CV_8U);
    channels[1].convertTo(channels[1], CV_8U);
    channels[2].convertTo(channels[2], CV_8U);

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

        switch(tolower(ch)){

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