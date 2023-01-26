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

int main(int argc, char** argv) 
{
    string path = argv[1];
    VideoCapture cap(path);
    
    if (!cap.isOpened())
    {
        cout<<"Failed"<<endl;
        return -1;
    }
    
    Mat frame;

    while(true)
    {
        cap >> frame;
        imshow("Original Video", frame);
        imshow("Line Detect", linedetect(frame));
        waitKey(20); // waits to display frame

        char c=(char)waitKey(25);
        if(c==27)
            break;
    }
    return 0;
}