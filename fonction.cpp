#include <string>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main() {

    string path = "Resources/vesco.jpg"; // Get file path
    Mat img = imread(path); //Read img
    Mat imgGray, imgBlur, imgCanny, imgDil, imgEro; //Create all imgs


    cvtColor(img, imgGray, COLOR_BGR2GRAY); //To black and white
    GaussianBlur(img, imgBlur, Size(3, 3), 3, 0); //Blurring
    Canny(imgBlur, imgCanny, 100, 150); //Get the edges

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5)); //Create kernel 
    dilate(imgCanny, imgDil, kernel);
    erode(imgDil, imgEro, kernel);

    imshow("Image", img);// Show our image inside the created window.
    imshow("Image Gray", imgGray);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDil);
    imshow("Image Erode", imgEro);


     waitKey(0); // Wait for any keystroke in the window


    /*string path2 = "Resources/test_video.mp4"; //Get video path
    VideoCapture cap(path2); //Create video type
    Mat img_v; //Create image

    while (true){
        cap.read(img_v); //Read video frames by frames

        imshow("Video", img_v); //Show each frames
        waitKey(0); //ms between each frames

    }*/
    return 0;
}
