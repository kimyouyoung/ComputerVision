#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    Mat frame;
    VideoCapture cap;

    // check if file exists. if non program ends
    if(cap.open("background.mp4") == 0){
        cout << "no such file!" << endl;
        waitKey(0);
    }
    
    while(cap.get(CAP_PROP_POS_MSEC)/1000 < 3){
        cap >> frame;
        if(frame.empty()){
            cout << "end of video" << endl;
            break;
        }
        imshow("video", frame);
        cout << "frames: " << cap.get(CAP_PROP_POS_FRAMES) << " / " << cap.get(CAP_PROP_FRAME_COUNT) << endl;
        waitKey(24);
    }

    double fps = cap.get(CAP_PROP_FPS);
    double time_in_msec = cap.get(CAP_PROP_POS_MSEC);
    int total_frames = cap.get(CAP_PROP_FRAME_COUNT);
}