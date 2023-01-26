#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

cv::Mat translate( cv::Mat img, int a, int b)
{
    Mat trans = Mat::zeros(img.rows + a, img.cols + b, CV_8UC3);

    int i, j, x, y;
    
    for(i = 0; i < img.rows; i++)
    {
        for(j = 0; j < img.cols; j++)
        {
            x = i + a;
            y = j + b;
            trans.at<Vec3b>(x,y) = img.at<Vec3b>(i,j);


        }
    }
    return trans;
}

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

cv::Mat scale( cv::Mat img, float s)
{
    Mat scaled = Mat::zeros(round(img.rows*s), round(img.cols*s), CV_8UC3);

    int i,j;
    
    for(i = 0; i < img.rows*s; i++)
    {
        for(j = 0; j < img.cols*s; j++)
        {
            scaled.at<Vec3b>(i,j) = img.at<Vec3b>(i/s,j/s);
        }
    }
    return scaled;
}

cv::Mat shear( cv::Mat img, float a)
{
    Mat sheared = Mat::zeros(img.rows , a * img.rows + img.cols, CV_8UC3);

    int i, j, x, y;
    
    for(i = 0; i < img.rows; i++)
    {
        for(j = 0; j < img.cols; j++)
        {
            x = i ;
            y = i * a + j;
            sheared.at<Vec3b>(x,y) = img.at<Vec3b>(i,j);
        }
    }
    return sheared;
}

cv::Mat affine(cv::Mat img, float matrix[2][3])
{
    int r = img.rows;
    int c = img.cols;
    Mat aff = Mat::zeros(ceil(r * matrix[0][0]  + matrix[0][1] * c + matrix[0][2]),
            ceil(matrix[1][0] * r + c *
             matrix[1][1]  + matrix[1][2]), CV_8UC3);
    int i, j;
    
    for(i = 0; i < img.rows; i++)
    {
        for(j = 0; j < img.cols; j++)
        {
            aff.at<Vec3b>(i * matrix[0][0]  + matrix[0][1] * j + matrix[0][2],
            matrix[1][0] * i + j * matrix[1][1]  + matrix[1][2]) = img.at<Vec3b>(i,j);
        }
    }
    return aff;
}

