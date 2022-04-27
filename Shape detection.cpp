#include <string>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<vector>
#include <iostream>

using namespace std;
using namespace cv;

Mat imgHSV, imgBlur, imgCanny, imgDil, imgEro;

void getContours(Mat imgDil, Mat img) {

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    string objectType;

    for (int i = 0; i < contours.size(); i = i + 1) {
        int area = contourArea(contours[i]);
        cout << area << endl;
        if (area > 1000) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            drawContours(img, conPoly, i, Scalar(255, 0, 255), 4);
            cout << conPoly[i].size() << endl;
            boundRect[i]= boundingRect(conPoly[i]);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 2);
            int objCor = (int)conPoly[i].size();
            if (objCor == 3) {
                objectType = "Triangle";
            }
            else if (objCor == 4) {
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                if (aspRatio > 0.95 && aspRatio < 1.05) {
                    objectType = "Square";
                }
                else {
                    objectType = "Rectangle";
                }
            }
            else if (objCor > 4) {
                objectType = "Circle";
            }
            putText(img, objectType, { boundRect[i].x, boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 1);
        }
    }
}

int main() {

    string path = "Resources/shapes3.png";
    Mat img = imread(path);
    imshow("Image", img);

    cvtColor(img, imgHSV, COLOR_BGR2HSV); //Color conversion
    GaussianBlur(imgHSV, imgBlur, Size(5, 5), 0, 0); //Blurring
    Canny(imgBlur, imgCanny, 100, 150); //Get the edges
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3)); //Create kernel
    dilate(imgCanny, imgDil, kernel);

    getContours(imgDil, img);


    imshow("Image", img);// Show our image inside the created window.
    imshow("Image Dil", imgDil);
    /*imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDil);*/

    waitKey(0);

    return 0;
}
