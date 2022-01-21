#include "opencv2/opencv.hpp"

#include "helpers.c"
using namespace cv;

double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
void fourPointTransform(Mat src, Mat &dst, std::vector<Point> pts);
cv::Point scalePointOrigin(cv::Point point, cv::Point origin, float scale);
cv::Point rotatePointOrigin(cv::Point point, cv::Point origin, float angle);
void orderPoints(std::vector<cv::Point> inpts, std::vector<cv::Point> &ordered);

double _distance(Point p1, Point p2);

Scalar ScalarHSV2BGR(uchar H, uchar S, uchar V);
bool compareAreas(std::vector<cv::Point> a, std::vector<cv::Point> b);
bool compareDistance(std::pair<Point, Point> p1, std::pair<Point, Point> p2);
