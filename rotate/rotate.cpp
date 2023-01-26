#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
using namespace cv;

cv::Mat rotate_alpha(cv::Mat img, float theta) 
{
    float alpha = CV_PI * theta / 180;
    int r = img.rows;
    int c = img.cols;
    int row  =  r * cos (alpha) + c * sin (alpha);
    int col = r * sin (alpha) + c * cos(alpha);

    int x, y;
    int i, j;

    Mat Rot(row, col, CV_8UC3);
    
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            x = round(i  * cos(alpha) - j * sin(alpha));
            y = round(i  * sin(alpha) + j * cos(alpha));

            Rot.at<Vec3b>(x + c * sin(alpha), y) = img.at<Vec3b>(i, j);
        }
    }
    return Rot;
}

cv::Mat rotate(cv::Mat img, float theta)
{
    if (theta < 90)
    {
        img = rotate_alpha(img, theta);
    }
    else if (theta >= 90)    
    {
        img = rotate(img, 89.999);
        theta = theta - 90;
        img = rotate(img, theta);
    }
    return img;
}

