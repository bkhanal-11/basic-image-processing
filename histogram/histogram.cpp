#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

double maximum(cv::Mat channel)
{
    double minVal, maxVal; 
    Point minLoc, maxLoc; 

    minMaxLoc(channel, &minVal, &maxVal, &minLoc, &maxLoc);

    return maxVal;
}

cv::Mat histPlotRGB(cv::Mat img)
{  
    int binSize = 256;
    float range[] = {0,256};
    const float* histRange = {range};
    
    vector<Mat> bgr_planes;
    split(img, bgr_planes);

    Mat blue, green, red;

    calcHist( &bgr_planes[0], 1, 0, Mat(), blue, 1, &binSize, &histRange, true, false);
    calcHist( &bgr_planes[1], 1, 0, Mat(), green, 1, &binSize, &histRange, true, false);
    calcHist( &bgr_planes[2], 1, 0, Mat(), red, 1, &binSize, &histRange, true, false);

    double value[] = {maximum(blue), maximum(green), maximum(red)};

    double max_ele = *max_element(value, value+3);

    int hist_w = max_ele*1.777777778; int hist_h = max_ele;
    int bin_w = cvRound( (double) hist_w/binSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 255,255,255) );

    for( int i = 1; i < binSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(blue.at<float>(i-1)) ) ,
                        Point( bin_w*(i), hist_h - cvRound(blue.at<float>(i)) ),
                        Scalar( 255, 0, 0), 3, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(green.at<float>(i-1))) ,
                        Point( bin_w*(i), hist_h - cvRound(green.at<float>(i))),
                        Scalar( 0, 255, 0), 3, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(red.at<float>(i-1)) ) ,
                        Point( bin_w*(i), hist_h - cvRound(red.at<float>(i)) ),
                        Scalar( 0, 0, 255), 3, 8, 0  );
    }
    return histImage;
}


cv::Mat histPlotGray(cv::Mat img)
{  
    int binSize = 256;
    float range[] = {0,256};
    const float* histRange = {range};
    
    vector<Mat> bgr_planes;
    split(img, bgr_planes);

    Mat gray;

    calcHist( &bgr_planes[0], 1, 0, Mat(), gray, 1, &binSize, &histRange, true, false);

    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/binSize );

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 255,255,255) );

    normalize(gray, gray, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < binSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(gray.at<float>(i-1)) ) ,
                        Point( bin_w*(i), hist_h - cvRound(gray.at<float>(i)) ),
                        Scalar( 0, 0, 0), 1, 8, 0 );
    }
    return histImage;
}

