#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <Eigen/Dense>
#include <stdio.h>
#include <iostream>

#include "header.h"

using namespace cv;
using namespace std;
using namespace Eigen;

int main(int argc, char** argv)
{
    string path = argv[1];
    string windowname;

    Mat img = imread(path);
    Mat imgOut;
    
    int n, a,b;
    float c;


    cout << "Enter the type of affine transform: 0 for translation, 1 for rotation,"
    " 2 for scale, 3 for shearing, 4 for random affine transform: ";
    cin >> n ;
    cout << endl;
  

    if (n == 0)
    {
        cout << "Enter translation coordinates: ";
        cin >> a >> b;
        cout << endl;
        imgOut = translate(img, a, b);
        windowname = "Translated Image";
    }
    else if (n == 1)
    {
        float theta;
        cout << "Enter angle of rotation: ";
        cin >> theta;
        imgOut = rotate(img, theta);
        windowname = "Rotated Image";
    }
    else if (n == 2)
    {
        int c;
        cout << "Enter Scaling Factor: ";
        cin >> c;
        imgOut = scale(img, c);
        windowname = "Scaled Image";
    }

    else if (n == 3)
    {
        cout << "Enter shear factor: ";
        cin >> c;
        cout << endl;
        imgOut = shear(img, c);
        windowname = "Sheared Image";
    }

    else if (n == 4)
    {
        float matrix[2][3];

        cout << "Enter 2 by 3 matrix elements (row by row):"<<endl;
        for(int i=0;i<2;i++)
        {
            cin >> matrix[i][0] >> matrix[i][1] >> matrix[i][2];
        }
        imgOut = affine(img, matrix);
        windowname = "Random Affine Transformed Image";
    }
    else
        return -1;


    imshow("Original Image", img);
    imshow(windowname, imgOut);
    waitKey(0);
    return 0;
}
