#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    Mat frame, canny_left, canny_right;
    VideoCapture cap;

    // check if file exists. if non program ends
    if(cap.open("Road.mp4") == 0){
        cout << "no such file!" << endl;
        waitKey(0);
    }

    Rect rect_left(200, 400, 400, 200);
    Rect rect_right(600, 400, 400, 200);

    while(1){
        cap >> frame;

        if(frame.empty()){
            cout << "end of video" << endl;
            break;
        }

        cvtColor(frame, frame, CV_BGR2GRAY);

        blur(frame, frame, Size(5, 5));

        Canny(frame, frame, 10, 60, 3);

        canny_left = frame(rect_left);
        canny_right = frame(rect_right);

        namedWindow("Left canny");
        moveWindow("Left canny", 200, 0);
        imshow("Left canny", canny_left);

        namedWindow("Right canny");
        moveWindow("Right canny", 600, 0);
        imshow("Right canny", canny_right);

        waitKey(1000/cap.get(CAP_PROP_FPS));
    }



    return 0;
}