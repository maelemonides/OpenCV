#include <string>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main() {

    Mat img(512, 512, CV_8UC3, Scalar(0,0,0)); // Choose color

    circle(img, Point(256,256), 155, Scalar(0, 69, 255), FILLED); // Choose circles center
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED); // What does points mean ? 
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);

    putText(img, "wsh le reuf", Point(200, 260), FONT_HERSHEY_TRIPLEX, 0.7, Scalar(0, 69, 255), 2); //What text to write ?

    imshow("img", img);

    waitKey(0);

    return 0;
}
