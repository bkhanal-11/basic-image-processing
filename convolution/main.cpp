#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

#include "header.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) 
{    
    Mat img;
    
    string path = argv[1];
    img = imread(path);

    if(!img.data )
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }

    int n, s;
    double o;
    cout << "Enter the dimension of kernel(odd, >= 3) (n by n): ";
    cin >> n;


    Mat kernel = Mat_<double>(n,n);

    for(int c = 0; c < n; c++)
    {
        for(int d = 0; d < n; d++)
        {
            cin >> o; 
            kernel.at<double>(c,d) = o; 
        }
    }

    cout << "Enter value for stride: ";
    cin >> s; 

    cout << "my kernel:\n "<< kernel << endl;
    Mat imgGray;
    cvtColor(img, imgGray, COLOR_BGR2GRAY);

    imshow("Original Image", img);
    imshow("Convolved Image", convolution(imgGray, kernel, s));

    waitKey(0);
    return 0;
}