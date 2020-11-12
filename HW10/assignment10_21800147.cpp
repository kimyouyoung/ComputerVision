#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    VideoCapture cap("background.mp4");
    Mat avg, frame, frame_gray, foregroundMask, result;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    double fps = cap.get(CV_CAP_PROP_FPS);
    int num_frame_avg = 10;
    int cnt = 1;
    int rect_num, i;

    // Read the first frame
    cap >> frame;
    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    avg = Mat(frame_gray.rows, frame_gray.cols, CV_8UC1, Scalar(0));
    add(frame_gray / num_frame_avg, avg, avg);

    for(int i = 0; i < 9; i++){
        cap >> frame;
        cvtColor(frame, frame_gray, CV_BGR2GRAY);
        add(frame_gray / num_frame_avg, avg, avg);
    }
   
    while(1){
        if(!cap.read(frame)) break;
        cvtColor(frame, frame_gray, CV_BGR2GRAY);
        result = frame_gray.clone();

        absdiff(avg, frame_gray, foregroundMask);
        threshold(foregroundMask, foregroundMask, 20, 255, CV_THRESH_BINARY);

        findContours(foregroundMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        vector<Rect> boundRect(contours.size());
        for(int i = 0; i < contours.size(); i++)
            boundRect[i] = boundingRect(Mat(contours[i]));
        
        int count = 0;
        for(int j = 0; j < contours.size(); j++){
            if(boundRect[j].area() > 400){
                count++;
                rectangle(result, boundRect[j].tl(), boundRect[j].br(), Scalar(255, 255, 255), 2, 8, 0);
            }
        }
        putText(result, format("# Rect: %d", count), Point(5, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
        imshow("background subtraction", result);

        waitKey(1000/cap.get(CAP_PROP_FPS));
    }
    
    waitKey(0);
    return 0;
}