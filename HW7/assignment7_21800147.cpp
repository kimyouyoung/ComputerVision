#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    Mat frame, edge, result;
    VideoCapture cap;
    vector<Vec2f> line_left, line_right;

    // check if file exists. if non program ends
    if(cap.open("Road.mp4") == 0){
        cout << "no such file!" << endl;
        waitKey(0);
    }

    float rho = 0, theta = 0, rho_r = 0, theta_r = 0;
    float rho_sum = 0, theta_sum = 0, rho_r_sum = 0, theta_r_sum = 0;
    float a, b, a_r, b_r, x0, y0, x0_r, y0_r; 
    Point p1, p2, p1_r, p2_r; 
    int count = 0, count_r = 0;

    Rect rect_left(200, 400, 400, 200);
    Rect rect_right(600, 400, 400, 200);

    while(cap.get(CAP_PROP_POS_MSEC)/1000 < 20){
        cap >> frame;
        result = frame.clone();

        cvtColor(frame, frame, CV_BGR2GRAY); 
        Canny(frame, edge, 50, 200, 3);


        HoughLines(edge(rect_left), line_left, 1, CV_PI / 180, 100);
        for (int i = 0; i < line_left.size(); i++) { 
            rho = line_left[i][0];
            theta = line_left[i][1];
            if((theta * 180 / CV_PI >= 30) && (theta * 180 / CV_PI <= 60)){
                rho_sum += rho;
                theta_sum += theta;
                count++;
            }
        }
        rho = rho_sum / count;
        theta = theta_sum / count;
        a = cos(theta);
        b = sin(theta);
        x0 = a * rho + 200; 
        y0 = b * rho + 400;
        p1 = Point(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * a)); 
        p2 = Point(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * a));
        line(result, p1, p2, Scalar(0, 0, 255), 3, 8); 

        HoughLines(edge(rect_right), line_right, 1, CV_PI / 180, 100);
        for (int i = 0; i < line_right.size(); i++) { 
            rho_r = line_right[i][0];
            theta_r = line_right[i][1];
            if((theta_r * 180 / CV_PI >= 120) && (theta_r * 180 / CV_PI <= 150)){
                rho_r_sum += rho_r;
                theta_r_sum += theta_r;
                count_r++;
            }
        }
        rho_r = rho_r_sum / count_r;
        theta_r = theta_r_sum / count_r;
        a_r = cos(theta_r);
        b_r = sin(theta_r);
        x0_r = a_r * rho_r + 600; 
        y0_r = b_r * rho_r + 400;
        p1_r = Point(cvRound(x0_r + 1000 * (-b_r)), cvRound(y0_r + 1000 * a_r)); 
        p2_r = Point(cvRound(x0_r - 1000 * (-b_r)), cvRound(y0_r - 1000 * a_r));
        line(result, p1_r, p2_r, Scalar(0, 0, 255), 3, 8); 

        imshow("Frame", result);

        waitKey(1000/cap.get(CAP_PROP_FPS));
    }

    return 0;
}