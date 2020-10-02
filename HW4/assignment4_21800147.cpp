#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat drawHistogram(Mat src){
    Mat hist, histImage;

    int hist_w, hist_h, bin_w, histSize;
    float range[] = {0, 256};
    const float* histRange = { range };

    hist_w = 512;
    hist_h = 512;
    histSize = 16;
    bin_w = cvRound((double)hist_w / histSize);

    histImage = Mat(hist_h, hist_w, CV_8U, Scalar(255, 255, 255));

    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for(int i = 0; i < histSize; i++){
        rectangle(histImage, Point(bin_w * i, hist_h), Point(bin_w * i+hist_w/histSize, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);   
    }

    return histImage;
}

Mat drawHistogram_text(Mat src){
    Mat hist;

    int hist_w, hist_h, bin_w, histSize;
    float range[] = {0, 256};
    const float* histRange = { range };

    hist_w = src.cols;
    hist_h = src.rows;
    histSize = 8;
    bin_w = cvRound((double)hist_w / histSize);

    calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

    for(int i = 0; i < histSize; i++){
        hist.at<float>(i) = hist.at<float>(i)/(hist_w*hist_h);
        string str = "bin " + to_string(i+1) + " : " + to_string(hist.at<float>(i));
        putText(src, str, Point(5, 25 + (25*i)), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255, 255, 255), 1);
    }

    return src;
}

int main(){

    Mat image, hist_equalized_image;
    
    image = imread("moon.png", 0);
    if(!image.data) exit(1);

    equalizeHist(image, hist_equalized_image);

    Mat hist_graph, hist_equalized_graph;
    hist_graph = drawHistogram(image);
    hist_equalized_graph = drawHistogram(hist_equalized_image);
    imshow("h1", hist_graph);
    imshow("h2", hist_equalized_graph);


    imshow("before", drawHistogram_text(image));
    
    imshow("after", drawHistogram_text(hist_equalized_image));

    waitKey(0);
    return 0;
}