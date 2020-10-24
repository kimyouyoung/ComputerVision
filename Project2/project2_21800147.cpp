#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    Mat frame, edge, result;
    VideoCapture cap;
    vector<Vec2f> line_left, line_mid, line_right;
    int count = 0;

    // check if file exists. if non program ends
    if(cap.open("Road.mp4") == 0){
        cout << "no such file!" << endl;
        waitKey(0);
    }

    Rect rect_left(170, 400, 400, 200);
    Rect rect_mid(570, 400, 130, 200);
    Rect rect_right(700, 400, 400, 200);

    while(cap.get(CAP_PROP_POS_MSEC)/1000 < 35){
        
        cap >> frame;
        result = frame.clone();

        float rho_left = 0, theta_left = 0, rho_right = 0, theta_right = 0;
        float rho_mid = 0, theta_mid = 0;
        bool left = false, right = false;
        bool mid = false;

        cvtColor(frame, frame, CV_BGR2GRAY); 
        Canny(frame, edge, 50, 200, 3);

        HoughLines(edge(rect_left), line_left, 1, CV_PI / 180, 70);
        for (int i = 0; i < line_left.size(); i++) { 
            theta_left = line_left[i][1];

            if((theta_left * 180 / CV_PI >= 30) && (theta_left * 180 / CV_PI <= 60)){
                left = true;
            }
        }

        HoughLines(edge(rect_right), line_right, 1, CV_PI / 180, 70);
        for (int i = 0; i < line_right.size(); i++) { 
            theta_right = line_right[i][1];

            if((theta_right * 180 / CV_PI >= 120) && (theta_right * 180 / CV_PI <= 150)){
                right = true;
            }
        }

        HoughLines(edge(rect_mid), line_mid, 1, CV_PI / 180, 70);
        for (int i = 0; i < line_mid.size(); i++) { 
            theta_mid = line_mid[i][1];

            if((theta_mid * 180 / CV_PI >= 30) && (theta_mid * 180 / CV_PI <= 60)){
                mid = true;
            }
            
            if((theta_mid * 180 / CV_PI >= 120) && (theta_mid * 180 / CV_PI <= 150)){
                mid = true;
            }
        }

        if(!left && !right){
            if(mid && count == 0){
                putText(result, format("Warning!: Lane departure"), Point(5, 50), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 3);
                count++;
            }
        }
        if(count != 0){
            putText(result, format("Warning!: Lane departure"), Point(5, 50), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 3);
            count++;
            if(count > 20){
                count = 0;
            }
        }
    
        imshow("Frame", result);

        waitKey(1000/cap.get(CAP_PROP_FPS));
    }
    
    return 0;
}
