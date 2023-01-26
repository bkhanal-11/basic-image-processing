#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat img;
    vector<Mat> imgList;
    vector<Mat> imgSort;
    vector<int> dimension;
    int i, m;

    vector<String> fn;
    string path  = argv[1];
    string ext = argv[2];
    string images = path + "*" + ext;

    glob(images, fn);
    for (auto f:fn)
    {
        img = imread(f);
        i = img.cols * img.rows;
        imgList.push_back(img);
        dimension.push_back(i); // number of pixels
    }


    for (vector<Mat>::iterator iter = imgList.begin(); iter != imgList.end(); iter++)
    {
        m = distance(dimension.begin(), min_element(dimension.begin(), dimension.end())); // argmax
        imgSort.push_back(imgList.at(m));
        dimension.erase(dimension.begin()+m);
        imgList.erase(imgList.begin()+m);
        if (imgList.empty())
        {
            break;
        }
    }

    for (vector<Mat>::iterator it = imgSort.begin(); it != imgSort.end(); it++)
    {
        imshow("Sorted Images", *it);
        waitKey(0);
    }
    return 0;
}