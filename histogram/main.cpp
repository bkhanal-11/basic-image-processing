#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

#include "header.h"

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <bits/stdc++.h> 

using namespace std;
using namespace cv;

int main()
{
    string path = "../../assets/room.jpg"; //initiating path for images                                                                                                                                               

    Mat img = imread(path);  //read the image from path   
    Mat blue, red, green;

    Mat imgGray, imgHSV;                                                                                                                                                         
    cv::cvtColor(img, imgGray, COLOR_BGR2GRAY);
    cv::cvtColor(img, imgHSV, COLOR_BGR2HSV);


    imshow("Original Image", img);                                                                                                                                                  
    imshow("GrayScaled OG Image",imgGray);
    imshow("OG Image in HSV color space", imgHSV);

    namedWindow("Histogram BGR", WINDOW_NORMAL);
    //resize the window according to the screen resolution
    resizeWindow("Histogram BGR", 960, 540);
    imshow("Histogram BGR", histPlotRGB(img));
    imshow("Histogram Gray", histPlotGray(imgGray));

    waitKey(0);
    return 0;
}
// #define CLAMP(x, upper, lower) (MIN(upper, MAX(x, lower)))
// double clamp(double x, double upper, double lower)
// {
//     return min(upper, max(x, lower));
// }

// int main()
// {   
//     string path = "../../assets/room.jpg"; //initiating path for images                                                                                                                                               

//     Mat src = imread(path);  //read the image from path
//     // "src" is the cv::Mat input image
//     const size_t number_of_channels = src.channels();
//     const cv::Scalar background_colour(0,0,0);

//     std::vector<cv::Mat> split;
//     cv::split(src, split);

//     const int       height          = 480;
//     const int       width           = 640;
//     const int       histogram_size  = 256; // the number of "bins"
//     const float     range[]         = {0, 256}; // upper bound is exclusive, meaning 0-255
//     const float *   ranges          = {range};
//     const bool      uniform         = true;
//     const bool      accumulate      = false;
//     cv::Mat         mask;

//     // prepare the destination image
//     const int margin        = 3;
//     const int min_y         = margin;
//     const int max_y         = height - margin;
//     const int thickness     = 1;
//     const int line_type     = cv::LINE_AA;
//     const float bin_width   = static_cast<float>(width) / static_cast<float>(histogram_size);
//     cv::Mat dst(height, width, CV_8UC3, background_colour); // create the output image, starting with a pure colour

//     cv::Scalar colours[] =
//     {
//         {255, 0, 0},    // blue
//         {0, 255, 0},    // green
//         {0, 0, 255}     // red
//     };
//     if (number_of_channels == 1)
//     {
//         // for greyscale images, we only have a single colour channel, so ignore
//         // the RGB colour definitions and use either black or white for the histogram

//         colours[0] = (background_colour == cv::Scalar(0, 0, 0)) ?
//                 cv::Scalar(255, 255, 255) :
//                 cv::Scalar(0, 0, 0);
//     }

//     // iterate through all the channels in this image
//     for (size_t idx=0; idx < split.size(); idx++)
//     {
//         const cv::Scalar colour = colours[idx % 3];

//         cv::Mat & m = split[idx];

//         cv::Mat histogram;
//         cv::calcHist(&m, 1, 0, mask, histogram, 1, &histogram_size, &ranges, uniform, accumulate);

//         cv::normalize(histogram, histogram, 0, dst.rows, cv::NORM_MINMAX);

//         for (int i = 1; i < histogram_size; i++)
//         {
//             const int x1 = std::round(bin_width * (i - 1));
//             const int x2 = std::round(bin_width * (i - 0));

//             const int y1 = CLAMP(height - static_cast<int>(std::round(histogram.at<float>(i - 1))), min_y, max_y);
//             const int y2 = CLAMP(height - static_cast<int>(std::round(histogram.at<float>(i - 0))), min_y, max_y);

//             cv::line(dst, cv::Point(x1, y1), cv::Point(x2, y2), colour, thickness, line_type);
//         }
//         cv::imshow("Histogram BGR", dst);

//     }
    
//     waitKey(0);
//     return 0;
// }

