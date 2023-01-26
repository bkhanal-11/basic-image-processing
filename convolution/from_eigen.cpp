#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>

using namespace std;
using namespace cv;
using namespace Eigen;

int main(int argc, char** argv)
{
    string path = argv[1];

    Mat img = imread(path);
    imshow("Original Image", img);
    img.convertTo(img, CV_64FC3);
    int n,s;

    cout << "Enter the dimension of kernel(odd, >= 3) (n by n): ";
    cin >> n;

    MatrixXf kernel(n,n);

    for(int c = 0; c < n; c++)
    {
        for(int d = 0; d < n; d++)
        {
            cin >> kernel(c,d); 
        }
    }
    cout << kernel<<endl;

    cout << "Enter value for stride: ";
    cin >> s; 

    int i,j,k,l;

    Mat imgPadded = Mat::zeros(img.rows + n - 1, img.cols + n - 1, CV_64FC3);

    for (int x = 0; x < img.rows; x++) 
    {
        for (int y = 0; y < img.cols; y++) 
        {
            imgPadded.at<Vec3d>(x+(n-1)/2,y+(n-1)/2)[0] = img.at<Vec3d>(x,y)[0];
            imgPadded.at<Vec3d>(x+(n-1)/2,y+(n-1)/2)[1] = img.at<Vec3d>(x,y)[1];
            imgPadded.at<Vec3d>(x+(n-1)/2,y+(n-1)/2)[2] = img.at<Vec3d>(x,y)[2];
        }
    }

    Mat imgConv  = Mat(img.rows / s  + 1, img.cols / s + 1, CV_64FC3);

    typedef Matrix<int, Dynamic, Dynamic> MatrixXd;
    MatrixXd mat_1, mat_2, mat_3;

    Mat channels[3];

    split(imgPadded, channels);

    cv2eigen(channels[0], mat_1);
    cv2eigen(channels[1], mat_2);
    cv2eigen(channels[2], mat_3);

    for(i = 0; i < img.rows; )
    {
        for(j = 0; j < img.cols; )
        {
            double sum_1 = 0;
            double sum_2 = 0;
            double sum_3 = 0;

            for(k = 0; k < n; k++)
            {
                for(l = 0; l < n; l++)
                {
                    sum_1 += mat_1(i + k, j + l) * kernel(k,l);
                    sum_2 += mat_2(i + k, j + l) * kernel(k,l);
                    sum_3 += mat_3(i + k, j + l) * kernel(k,l);
                }
            }

            imgConv.at<Vec3d>(i/s,j/s)[0] = sum_1;
            imgConv.at<Vec3d>(i/s,j/s)[1] = sum_2;
            imgConv.at<Vec3d>(i/s,j/s)[2] = sum_3;
            j = j + s;
        }
        i = i + s;
    }
    
    imgConv.convertTo(imgConv, CV_8UC3);

    imshow("Convolved Image", imgConv);
    
    waitKey(0);
    return 0;
}