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

    Rect rect_left(200, 400, 400, 200);
    Rect rect_right(600, 400, 400, 200);

    while(cap.get(CAP_PROP_POS_MSEC)/1000 < 20){
        
        cap >> frame;
        result = frame.clone();

        float rho_left = 0, theta_left = 0, rho_right = 0, theta_right = 0;
        float rho_left_sum = 0, theta_left_sum = 0, rho_right_sum = 0, theta_right_sum = 0;
        float rho_left_avg = 0, theta_left_avg = 0, rho_right_avg = 0, theta_right_avg = 0;
        float a_left, b_left, a_right, b_right, x0_left, y0_left, x0_right, y0_right; 
        Point p1_left, p2_left, p1_right, p2_right; 
        int count_left = 0, count_right = 0;
        bool left = false, right = false;

        cvtColor(frame, frame, CV_BGR2GRAY); 
        Canny(frame, edge, 50, 200, 3);

        HoughLines(edge(rect_left), line_left, 1, CV_PI / 180, 70);
        for (int i = 0; i < line_left.size(); i++) { 
            rho_left = line_left[i][0];
            theta_left = line_left[i][1];
            if((theta_left * 180 / CV_PI >= 30) && (theta_left * 180 / CV_PI <= 60)){
                rho_left_sum += rho_left;
                theta_left_sum += theta_left;
                count_left++;
                left = true;
            }
        }
        if(left){
            rho_left_avg = rho_left_sum / count_left;
            theta_left_avg = theta_left_sum / count_left;

            a_left = cos(theta_left_avg);
            b_left = sin(theta_left_avg);

            x0_left = a_left * rho_left_avg + 200; 
            y0_left = b_left * rho_left_avg + 400;

            p1_left = Point(cvRound(x0_left + 1000 * (-b_left)), cvRound(y0_left + 1000 * a_left)); 
            p2_left = Point(cvRound(x0_left - 1000 * (-b_left)), cvRound(y0_left - 1000 * a_left));

            line(result, p1_left, p2_left, Scalar(0, 0, 255), 3, 8); 
        }

        HoughLines(edge(rect_right), line_right, 1, CV_PI / 180, 70);
        for (int i = 0; i < line_right.size(); i++) { 
            rho_right = line_right[i][0];
            theta_right = line_right[i][1];
            if((theta_right * 180 / CV_PI >= 120) && (theta_right * 180 / CV_PI <= 150)){
                rho_right_sum += rho_right;
                theta_right_sum += theta_right;
                count_right++;
                right = true;
            }
        }
        if(right){
            rho_right_avg = rho_right_sum / count_right;
            theta_right_avg = theta_right_sum / count_right;

            a_right = cos(theta_right_avg);
            b_right = sin(theta_right_avg);

            x0_right = a_right * rho_right_avg + 600; 
            y0_right = b_right * rho_right_avg + 400;

            p1_right = Point(cvRound(x0_right + 1000 * (-b_right)), cvRound(y0_right + 1000 * a_right)); 
            p2_right = Point(cvRound(x0_right - 1000 * (-b_right)), cvRound(y0_right - 1000 * a_right));

            line(result, p1_right, p2_right, Scalar(0, 0, 255), 3, 8); 
        }

        imshow("Frame", result);

        waitKey(1000/cap.get(CAP_PROP_FPS));
    }

    return 0;
}