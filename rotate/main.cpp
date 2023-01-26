#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <stdio.h>

#include "header.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) 
{
    string path = argv[1];
 
    Mat img = imread(path);

    float theta;

    cout << "Enter the angle of rotation: ";
    cin >> theta;


    imshow("Original Image", img);

    namedWindow("Rotated Image",WINDOW_AUTOSIZE); 
    imshow("Rotated Image", rotate(img, theta));

    waitKey(0);
    return 0;
}