#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

cv::Mat gaussian_blur(cv::Mat img, int kernel)
{
    Mat imgGaussian;
    GaussianBlur(img, imgGaussian, Size(kernel, kernel), 1.0);
    return imgGaussian;
}