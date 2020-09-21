#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat drawHistogram(Mat src, int num_bins){
    Mat hist, histImage;

    int hist_w, hist_h, bin_w, histSize;
    float range[] = {0, 255};
    const float* histRange = { range };

    hist_w = 512;
    hist_h = 512;
    histSize = num_bins;
    bin_w = cvRound((double)hist_w / histSize);

    histImage = Mat(hist_h, hist_w, CV_8U, Scalar(255, 255, 255));

    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for(int i = 0; i < histSize; i++){

    rectangle(histImage, Point(bin_w * i, hist_h), Point(bin_w * i+hist_w/histSize, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);    }

    return histImage;
}

int main(){

    Mat image, hist_equalized_image;
    
    image = imread("moon.png", 0);
    if(!image.data) exit(1);

    equalizeHist(image, hist_equalized_image);

    Mat hist_graph, hist_equalized_graph;
    hist_graph = drawHistogram(image, 16);
    hist_equalized_graph = drawHistogram(hist_equalized_image, 16);
    imshow("h1", hist_graph);
    imshow("h2", hist_equalized_graph);

    int one, two, three, four, five, six, seven, eight;
    for(int i = 0; i < image.rows; i++){
        for(int j = 0; j < image.cols; j++){
            if(image.at<uchar>(i, j) >= 0 && image.at<uchar>(i, j) < 32)
                one++;
            else if(image.at<uchar>(i, j) >= 32 && image.at<uchar>(i, j) < 64)
                two++;
            else if(image.at<uchar>(i, j) >= 64 && image.at<uchar>(i, j) < 96)
                three++;
            else if(image.at<uchar>(i, j) >= 96 && image.at<uchar>(i, j) < 128)
                four++;
            else if(image.at<uchar>(i, j) >= 128 && image.at<uchar>(i, j) < 160)
                five++;
            else if(image.at<uchar>(i, j) >= 160 && image.at<uchar>(i, j) < 192)
                six++;
            else if(image.at<uchar>(i, j) >= 192 && image.at<uchar>(i, j) < 224)
                seven++;
            else
                eight++;
        }
    }

    string str, str2, str3, str4;
    str = "1st bin: " + to_string((float)(one)/(image.cols*image.rows)) + ", 2nd bin: " + to_string((float)(two)/(image.cols*image.rows));
    str2 = "3rd bin: " + to_string((float)(three)/(image.cols*image.rows)) + ", 4th bin: " + to_string((float)(four)/(image.cols*image.rows));
    str3 = "5th bin: " + to_string((float)(five)/(image.cols*image.rows)) + ", 6th bin: " + to_string((float)(six)/(image.cols*image.rows));
    str4 =  "7th bin: " + to_string((float)(seven)/(image.cols*image.rows)) + ", 8th bin: " + to_string((float)(eight)/(image.cols*image.rows)); 

    putText(image, str, Point(5, 25), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 100, 200), 1);
    putText(image, str2, Point(5, 50), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 100, 200), 1);
    putText(image, str3, Point(5, 75), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 100, 200), 1);
    putText(image, str4, Point(5, 100), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 100, 200), 1);
    imshow("before", image);

    for(int i = 0; i < hist_equalized_image.rows; i++){
        for(int j = 0; j < hist_equalized_image.cols; j++){
            if(hist_equalized_image.at<uchar>(i, j) >= 0 && hist_equalized_image.at<uchar>(i, j) < 32)
                one++;
            else if(hist_equalized_image.at<uchar>(i, j) >= 32 && hist_equalized_image.at<uchar>(i, j) < 64)
                two++;
            else if(hist_equalized_image.at<uchar>(i, j) >= 64 && hist_equalized_image.at<uchar>(i, j) < 96)
                three++;
            else if(hist_equalized_image.at<uchar>(i, j) >= 96 && hist_equalized_image.at<uchar>(i, j) < 128)
                four++;
            else if(hist_equalized_image.at<uchar>(i, j) >= 128 && hist_equalized_image.at<uchar>(i, j) < 160)
                five++;
            else if(hist_equalized_image.at<uchar>(i, j) >= 160 && hist_equalized_image.at<uchar>(i, j) < 192)
                six++;
            else if(hist_equalized_image.at<uchar>(i, j) >= 192 && hist_equalized_image.at<uchar>(i, j) < 224)
                seven++;
            else
                eight++;
        }
    }

    str = "1st bin: " + to_string((float)(one)/(hist_equalized_image.cols*hist_equalized_image.rows)) + ", 2nd bin: " + to_string((float)(two)/(hist_equalized_image.cols*hist_equalized_image.rows));
    str2 = "3rd bin: " + to_string((float)(three)/(hist_equalized_image.cols*hist_equalized_image.rows)) + ", 4th bin: " + to_string((float)(four)/(hist_equalized_image.cols*hist_equalized_image.rows));
    str3 = "5th bin: " + to_string((float)(five)/(hist_equalized_image.cols*hist_equalized_image.rows)) + ", 6th bin: " + to_string((float)(six)/(hist_equalized_image.cols*hist_equalized_image.rows));
    str4 =  "7th bin: " + to_string((float)(seven)/(hist_equalized_image.cols*hist_equalized_image.rows)) + ", 8th bin: " + to_string((float)(eight)/(hist_equalized_image.cols*hist_equalized_image.rows)); 

    putText(hist_equalized_image, str, Point(5, 25), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 100, 200), 1);
    putText(hist_equalized_image, str2, Point(5, 50), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 100, 200), 1);
    putText(hist_equalized_image, str3, Point(5, 75), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 100, 200), 1);
    putText(hist_equalized_image, str4, Point(5, 100), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 100, 200), 1);
    imshow("after", hist_equalized_image);

    waitKey(0);
    return 0;
}