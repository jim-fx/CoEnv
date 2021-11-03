#ifndef FILTER_H
#define FILTER_H

#include "opencv2/opencv.hpp"

using namespace cv;

Mat filterCanny(Mat input);
Mat splitMat(Mat inputA, Mat inputB);

#endif
