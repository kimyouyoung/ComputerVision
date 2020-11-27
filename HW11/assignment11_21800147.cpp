#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    VideoCapture cap("background.mp4");
    Mat avg, frame, frame_gray, sub, element, element2, closing, result, roi, roi2, roi3;
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
   
   Rect rect(0, 0, frame.cols - 100, frame.rows);
   Rect rect2(frame.cols - 100, 0, 100, frame.rows / 2);
   Rect rect3(frame.cols - 100, frame.rows / 2, 100, frame.rows / 2);

    while(1){
        cap >> frame;
        result = frame.clone();
        cvtColor(frame, frame_gray, CV_BGR2GRAY);
        
        if(cnt < 10){
            add(frame_gray / num_frame_avg, avg, avg);
            cnt++;
        }else{
            absdiff(avg, frame_gray, sub);
            roi = sub(rect);
            roi2 = sub(rect2);
            roi3 = sub(rect3);
            threshold(roi, roi, 20, 255, THRESH_BINARY);
            threshold(roi2, roi2, 20, 255, THRESH_BINARY);
            threshold(roi3, roi3, 60, 255, THRESH_BINARY);
            element = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));
            element2 = getStructuringElement(MORPH_ELLIPSE, Size(2, 2));
            dilate(sub, closing, element2);
            erode(closing, closing, element2);
            morphologyEx(closing, closing, MORPH_CLOSE, element);
            
            findContours(closing, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

            vector<Rect> boundRect(contours.size());
            rect_num = 0;
            for(i = 0; i < contours.size(); i++){
                boundRect[i] = boundingRect(contours[i]);
                if(boundRect[i].area() > 1000){
                    rectangle(result, boundRect[i], Scalar(255, 255, 255), 2, 8);
                    rect_num++;
                }
            }

            putText(result, format("#People: %d", rect_num), Point2f(10, 30), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);
            imshow("Number of people", result);
        }

        waitKey(1000/fps);
    }
    
    waitKey(0);
    return 0;
}