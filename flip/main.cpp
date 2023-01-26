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

    
    Mat img = imread(path);

    Mat imgHori, imgVert, imgGray;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);


    imshow("Original Image", img);
    imshow("Horizontally Flipped Image", flip_H(img));
    imshow("Vertically Flipped Image", flip_V(img));

    imshow("Horizontally Flipped Image (Gray)", flip_H(imgGray));
    imshow("Vertically Flipped Image (Gray)", flip_V(imgGray));

    waitKey(0);
    return 0;
}