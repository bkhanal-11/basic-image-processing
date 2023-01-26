#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

cv::Mat flip_H(cv::Mat img) 
{
    Mat imgflip_h = img.clone();
    int i, j, k;

    if (img.channels() == 3)
    {
        for(i = 0; i < img.rows; i++)
        {
            for(j = 0; j < img.cols; j++)
            {
                imgflip_h.at<Vec3b>(i,j) = img.at<Vec3b>(i,img.cols - (j + 1));
            }
        }
    }

    if (img.channels() == 1)
    {
        for(i = 0; i < img.rows; i++)
        {
            for(j = 0; j < img.cols; j++)
            {
                imgflip_h.at<uchar>(i,j) = img.at<uchar>(i,img.cols - (j + 1));
            }
        }
    }
    return imgflip_h;
}

cv::Mat flip_V(cv::Mat img) 
{
    Mat imgflip_v = img.clone();
    int i, j;

    if (img.channels() == 3)
    {
        for(i = 0; i < img.rows; i++)
        {
            for(j = 0; j < img.cols; j++)
            {
                imgflip_v.at<Vec3b>(i,j) = img.at<Vec3b>(img.rows - (i + 1), j);
            }
        }
    }

    if (img.channels() == 1)
    {
        for(i = 0; i < img.rows; i++)
        {
            for(j = 0; j < img.cols; j++)
            {
                imgflip_v.at<uchar>(i,j) = img.at<uchar>(img.rows - (i + 1), j);
            }
        }
    }
    return imgflip_v;
}
