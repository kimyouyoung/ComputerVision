#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main(){

    VideoCapture cap(0);
    CascadeClassifier face_classifier;
    Mat frame, grayframe, hsv;
    Mat result, bgModel, fgModel, image, background;
    Mat m_backproj, m_model3d;
    Rect m_rc;
    float hrange[] = { 0,180 };
    float vrange[] = { 0,255 };
    float srange[] = { 0,255 };
    const float* ranges[] = { hrange, srange, vrange };
    int channels[] = {0, 1, 2};
    int hist_sizes[] = { 16, 16, 16 };
    vector<Rect> faces;
    
    if(!cap.isOpened()){
        cout << "can't open video file" << endl;
        return 0;
    }
    double fps = cap.get(CV_CAP_PROP_FPS);
    
    cap >> frame;
    image = imread("background.jpg");
    resize(image, image, Size(frame.cols/5, frame.rows/5));

    face_classifier.load("/Users/youyoungkim/Downloads/opencv-3.4.6/data/haarcascades/haarcascade_frontalface_alt.xml");
    int count = 0;
    int idx_max = 0;

    bool tracking = false;
    while(true){

        cap >> frame;
        
        resize(frame, frame, Size(frame.cols/5, frame.rows/5));
        if(frame.empty()){
            cout << "end of video" << endl;
            break;
        }
        if(count % 2 == 0){
            cvtColor(frame, grayframe, COLOR_BGR2GRAY);
            face_classifier.detectMultiScale(
                grayframe,
                faces,
                1.1,
                3,
                0,
                Size(60, 60)
            );

            int max = faces[0].area();
            for(int i = 0; i < faces.size(); i++){
                if(max < faces[i].area()){
                    max = faces[i].area();
                    idx_max = i;
                }
            }
            count = 0;
            tracking = false;
        }
        else{
            tracking = true;
        }
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        Rect rc = faces[idx_max];
        Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
        ellipse(mask, Point(rc.width/2, rc.height/2), Size(rc.width/2, rc.height/2), 0, 0, 360, 255, CV_FILLED);
        Mat roi(hsv, rc);
        calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
        m_rc = rc;

        if(tracking){
            calcBackProject(&hsv, 1, channels, m_model3d, m_backproj, ranges);
            CamShift(m_backproj, m_rc, cvTermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 20,1));
        }
        grabCut(frame, result, m_rc, bgModel, fgModel, 3, GC_INIT_WITH_RECT);
        compare(result, GC_PR_FGD, result, CMP_EQ);

        background = image.clone();
        frame.copyTo(background, result);

        imshow("Project3", background);
        waitKey(1000/fps);
        count++;
    }

    return 0;
}