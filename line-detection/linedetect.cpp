#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

cv::Mat linedetect(cv::Mat img) 
{
    Mat imgGray, imgCanny, linedet;
    vector<Vec2f> lines;
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    Canny(imgGray, imgCanny, 200, 250, 3);

    cvtColor(imgCanny, linedet, COLOR_GRAY2BGR);

    HoughLines(imgCanny, lines, 1, CV_PI/180, 200, 0, 0 );

    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        
        line(img, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    }
    return img;
}