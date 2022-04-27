#include <string>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>


using namespace std;
using namespace cv;

int main() {
    vector<String> fn;

    vector<Mat> images;
    Mat imgGray;
    vector<Rect> Face;                      // Create vector of rectangle 
    int n = 0;
    /*double scale = 2;*/

    //glob("Fam2a/*.jpg", fn, false);
    glob("cat/*.jpg", fn, false);
    size_t count = fn.size();

    for (size_t i = 0; i < count; i++) {
        images.push_back(imread(fn[i]));
    }

    for (Mat i : images) {


        cvtColor(i, imgGray, COLOR_BGR2GRAY); //Convert to gray
        resize(imgGray, imgGray, Size(imgGray.size().width, imgGray.size().height)); //Resize

        

        CascadeClassifier Cascade;            // Load face recognition model
        //Cascade.load("Resources/haarcascade_frontalface_alt.xml");
        Cascade.load("Resources/haarcascade_frontalcatface.xml");
        Cascade.detectMultiScale(imgGray, Face, 1.1, 10, 0, Size(75,75));
        


        if (Cascade.empty()) {
            cout << "XML file not loaded" << endl;
        }

        for (int k = 0; k < Face.size(); k = k + 1) {
            rectangle(i, Face[k].tl(), Face[k].br(), Scalar(255, 0, 255), 3);
        }

        putText(i, "Person Count : " + to_string(Face.size()), Point(20, 40), FONT_HERSHEY_TRIPLEX, 1, Scalar(255, 0, 255), 2);

        /*for (Rect area : Face) {
            Scalar drawColor = Scalar(255, 0, 0);
            rectangle(i, Point(cvRound(area.x*scale), cvRound(area.y*scale)),
                Point(cvRound((area.x + area.width - 1)*scale), cvRound((area.y + area.height - 1)*scale)), drawColor);
        }*/

        imshow("famille" + to_string(n), i); //Show each frames
        n = n + 1;

        waitKey(0); //ms between each frames
    }
    return 0;
}

    
