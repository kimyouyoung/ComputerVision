#include "cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    CascadeClassifier face_classifier;
    Mat frame, grayframe;
    vector<Rect> faces;
    Rect result_face;
    VideoCapture cap;
    char ch = ' ';
    char act = ' ';

    // check if file exists. if non program ends
    if(cap.open("Faces.mp4") == 0){
        cout << "no such file!" << endl;
        waitKey(0);
    }

    double fps = cap.get(CV_CAP_PROP_FPS);

    // face detection configuration
    face_classifier.load("/Users/youyoungkim/Downloads/opencv-3.4.6/data/haarcascades/haarcascade_frontalface_alt.xml");


    while(true){
        cap >> frame;

        if(frame.empty()){
            cout << "end of video" << endl;
            break;
        }
        
        cvtColor(frame, grayframe, COLOR_BGR2GRAY);
        face_classifier.detectMultiScale(
            grayframe,
            faces,
            1.1,
            3,
            0,
            Size(30, 30),
            Size(90, 90)
        );
        int idx_max = 0;
        int max = faces[0].area();
        for(int i = 0; i < faces.size(); i++){
            if(max < faces[i].area()){
                max = faces[i].area();
                idx_max = i;
            }
        }

        int idx_min = 0;
        int min = faces[0].area();
        for(int i = 0; i < faces.size(); i++){
            if(min > faces[i].area()){
                min = faces[i].area();
                idx_min = i;
            }
        }
        
        switch(tolower(act)){
            case 'n': {
                Point lb(faces[idx_max].x + faces[idx_max].width, faces[idx_max].y + faces[idx_max].height);
                Point tr(faces[idx_max].x, faces[idx_max].y);
                rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
                break;
            }
            
            case 'f':{
                Point lb(faces[idx_min].x + faces[idx_min].width, faces[idx_min].y + faces[idx_min].height);
                Point tr(faces[idx_min].x, faces[idx_min].y);
                rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
                break;
            }

            case 'm':{
                for(int i = 0; i < faces.size(); i++){
                    if(i != idx_max && i != idx_min && faces[i].area() > 50){
                        Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
                        Point tr(faces[i].x, faces[i].y);
                        rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
                        break;
                    }
                }
                break;
            }
        }

        imshow("Faces", frame);
        ch = waitKey(1000/fps);
        int num = ch - '0';
        if(ch != act && num != -49)
            act = ch;
        
    }

    return 0;
}