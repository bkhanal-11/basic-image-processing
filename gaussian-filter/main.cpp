#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "header.h"

using namespace std;
using namespace cv;

int main()
{
    string path = "../assets/room.jpg"; //initiating path for images
    
    Mat img = imread(path);  //read the image from path


    imshow("Original Image", img);  //displaying the original image
    imshow("Blurred Image with Gaussian Blur", gaussian_blur(img, 7));
    imshow("Canny Edge Detection", edgedetect(img, 25, 75, 3));
    imshow("Dilated Canny image", dilation(edgedetect(img, 25, 75, 3), 3));
    imshow("Eroded Dilated Image", errosion(dilation(edgedetect(img, 25, 75, 3), 3), 3));


    waitKey(0);
    return 0;
}