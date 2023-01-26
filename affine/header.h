cv::Mat translate(cv::Mat, int, int);
cv::Mat rotate(cv::Mat, float);
cv::Mat rotate_alpha(cv::Mat, float);
cv::Mat scale(cv::Mat, float);
cv::Mat shear(cv::Mat, float);
cv::Mat affine(cv::Mat, float(*)[3]);
