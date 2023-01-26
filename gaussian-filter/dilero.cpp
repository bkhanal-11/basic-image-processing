#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

cv::Mat dilation(cv::Mat img, int size)
{
    Mat imgdil;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(size,size));
    dilate(img, imgdil,kernel);
    return imgdil;
}

cv::Mat errosion(cv::Mat img, int size)
{
    Mat imgErr;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(size,size));
    erode(img, imgErr,kernel);
    return imgErr;
}