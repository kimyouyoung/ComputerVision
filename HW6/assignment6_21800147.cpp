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

        canny_left = frame(rect_left);
        canny_right = frame(rect_right);

        cvtColor(canny_left, canny_left, CV_BGR2GRAY);
        cvtColor(canny_right, canny_right, CV_BGR2GRAY);

        blur(canny_left, canny_left, Size(5, 5));
        blur(canny_right, canny_right, Size(5, 5));

        Canny(canny_left, canny_left, 10, 60, 3);
        Canny(canny_right, canny_right, 10, 60, 3);

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