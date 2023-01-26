#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

cv::Mat convolution1(cv::Mat img, cv::Mat kernel, int s) 
{    
    Mat imgPadd, imgConv;

    // img.convertTo(img, CV_64FC1);

    int n = kernel.rows;

    // Zero-Padding
    imgPadd = Mat::zeros(img.rows + n - 1, img.cols + n - 1, CV_8UC1);

    for (int x=0; x<img.rows; x++) 
    {
        for (int y=0; y<img.cols; y++) 
        {
            imgPadd.at<uchar>(x+(n-1)/2,y+(n-1)/2) = img.at<uchar>(x,y);
        }
    }

    //Performing the convolution
    imgConv = Mat(img.rows / s + 1, img.cols / s + 1, CV_8UC1);

    for (int x=(n-1)/2; x<imgPadd.rows-((n-1)/2); ) 
    {
        for (int y=(n-1)/2; y<imgPadd.cols-((n-1)/2); ) 
        {
            double sum_1=0;
                for (int u = -(n-1)/2; u <= (n-1)/2; u++) 
                {
                    for (int v = -(n-1)/2; v <= (n-1)/2; v++) 
                    {
                        sum_1 += imgPadd.at<uchar>(x+u,y+v) * kernel.at<double>(u + ((n-1)/2) ,v + ((n-1)/2));
                    }
                }
            imgConv.at<uchar>((x-((n-1)/2))/s,(y-(n-1)/2)/s) = sum_1;
            y = y + s;
        }
        x = x + s;
    }
    // imgConv.convertTo(imgConv, CV_8UC1);

    return imgConv;
}

cv::Mat convolution3(cv::Mat img, cv::Mat kernel, int s) 
{    
    Mat imgPadd, imgConv;

    img.convertTo(img, CV_64FC3);

    int n = kernel.rows;

    // Zero-Padding
    imgPadd = Mat::zeros(img.rows + n - 1, img.cols + n - 1, CV_64FC3);

    for (int x=0; x<img.rows; x++) 
    {
        for (int y=0; y<img.cols; y++) 
        {
            imgPadd.at<Vec3d>(x+(n-1)/2,y+(n-1)/2)[0] = img.at<Vec3d>(x,y)[0];
            imgPadd.at<Vec3d>(x+(n-1)/2,y+(n-1)/2)[1] = img.at<Vec3d>(x,y)[1];
            imgPadd.at<Vec3d>(x+(n-1)/2,y+(n-1)/2)[2] = img.at<Vec3d>(x,y)[2];
        }
    }

    //Performing the convolution
    imgConv = Mat(img.rows / s + 1, img.cols / s + 1, CV_64FC3);

    for (int x=(n-1)/2; x<imgPadd.rows-((n-1)/2); ) 
    {
        for (int y=(n-1)/2; y<imgPadd.cols-((n-1)/2); ) 
        {
            double sum_1=0;
            double sum_2=0;
            double sum_3=0;
                for (int u = -(n-1)/2; u <= (n-1)/2; u++) 
                {
                    for (int v = -(n-1)/2; v <= (n-1)/2; v++) 
                    {
                        sum_1 += imgPadd.at<Vec3d>(x+u,y+v)[0] * kernel.at<double>(u + ((n-1)/2) ,v + ((n-1)/2));
                        sum_2 += imgPadd.at<Vec3d>(x+u,y+v)[1] * kernel.at<double>(u + ((n-1)/2),v + ((n-1)/2));
                        sum_3 += imgPadd.at<Vec3d>(x+u,y+v)[2] * kernel.at<double>(u +  ((n-1)/2),v + ((n-1)/2));
                    }
                }
            imgConv.at<Vec3d>((x-((n-1)/2))/s,(y-(n-1)/2)/s)[0] = sum_1;
            imgConv.at<Vec3d>((x-((n-1)/2))/s,(y-(n-1)/2)/s)[1] = sum_2;
            imgConv.at<Vec3d>((x-((n-1)/2))/s,(y-(n-1)/2)/s)[2] = sum_3;
            y = y + s;
        }
        x = x + s;
    }
    imgConv.convertTo(imgConv, CV_8UC3);

    return imgConv;
}

cv::Mat convolution(cv::Mat img, cv::Mat kernel, int s)
{
    int channel = img.channels();

    if (channel == 1)
    {
        return convolution1(img, kernel, s);
    }
    else
    {
        return convolution3(img, kernel, s);
    }
} 