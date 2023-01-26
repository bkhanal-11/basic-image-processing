#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

cv::Mat edgedetect(cv::Mat img, int thres1, int thres2, int width)
{
    Mat imgCanny;
    Canny(img, imgCanny, thres1, thres2, width);
    return imgCanny;
}