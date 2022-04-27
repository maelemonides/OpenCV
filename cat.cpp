#include <string>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>


using namespace std;
using namespace cv;

int main() {

    for (int i = 2; i < 150; i = i + 1) {
        //string path = "dog/flickr_dog_00000" + to_string(i) + ".jpg";
        string path = "cat/cat." + to_string(i) + ".jpg";// Get file path
        Mat img, imgGray;                         // Create video container
        vector<Rect> catFace;                      // Create vector of rectangle 
        img = imread(path);                     //Read frames

        cvtColor(img, imgGray, COLOR_BGR2GRAY); //Convert to gray

        CascadeClassifier Cascade;            // Load face recognition model
        Cascade.load("Resources/haarcascade_frontalcatface_alt.xml");
        Cascade.detectMultiScale(imgGray, catFace, 1.1, 6, 0, Size(75, 75));



        if (Cascade.empty()) {
            cout << "XML file not loaded" << endl;
        }

        for (int i = 0; i < catFace.size(); i = i + 1) {
            rectangle(img, catFace[i].tl(), catFace[i].br(), Scalar(255, 0, 255), 3);
        }

        /*for (Rect area : catFace) {
            Scalar drawColor = Scalar(255, 0, 0);
            rectangle(img, Point(cvRound(area.x), cvRound(area.y)),
                Point(cvRound(area.x + area.width - 1), cvRound(area.y + area.height - 1)), drawColor);
        }*/

        imshow("chat" + to_string(i), img); //Show each frames
        waitKey(0); //ms between each frames
    }
    return 0;
}