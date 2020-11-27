#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

struct CallbackParam{
    Mat frame;
    Point p1, p2;
    Rect roi;
    bool drag;
    bool updated;
};

int main(){

    VideoCapture cap(0);
    CallbackParam param;
    Mat frame, m_backproj, hsv;
    Mat m_model3d;
    Rect m_rc;
    float hrange[] = {0, 180};
    float vrange[] = {0, 255};
    float srange[] = {0, 255};
    const float* ranges[] = {hrange, srange, vrange};
    int channels[] = {0, 1, 2};
    int hist_sizes[] = {16, 16, 16};
    Mat result, bgModel, fgModel, image;
    double fps = cap.get(CV_CAP_PROP_FPS);

    if(!cap.isOpened()){
        cout << "can't open video file" << endl;
        return 0;
    }

    cap >> frame;
    imshow("Tracker", frame);
    param.frame = frame;
    param.drag = false;
    param.updated = false;
    
    bool tracking = false;

    while(true){
        if(param.drag){
            if(waitKey(1000/fps) == 27) break;
            continue;
        }
        cvtColor(frame, hsv, COLOR_BGR2HSV);

        if(param.updated){
            Rect rc = param.roi;
            Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
            ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255, CV_FILLED);
            Mat roi(hsv, rc);
            calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
            m_rc = rc;
            param.updated = false;
            tracking = true;
        }
        cap >> frame;
        result = frame.clone();
        if(frame.empty()) break;

        if(tracking){
            calcBackProject(&hsv, 1, channels, m_model3d, m_backproj, ranges);
            CamShift(m_backproj, m_rc, cvTermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 20, 1));
            // rectangle(frame, m_rc, Scalar(0, 0, 255), 3);
            grabCut(frame, result, m_rc, bgModel, fgModel, 10, GC_INIT_WITH_RECT);
            compare(result, GC_PR_FGD, result, CMP_EQ);
            image = imread("balancing.jpg");
            image.copyTo(result);
        }

        imshow("Tracker", result);

        char ch = waitKey(1000/fps);
        if(ch == 27) break;
    }

    return 0;
}