#ifndef FILTER_H
#define FILTER_H

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include <cstdio>
#include <opencv2/core.hpp>

using namespace cv;

Mat filterCanny(Mat input, int vA, int vB, int vC) {

  Mat blurred;
  GaussianBlur(input, blurred, Size(11, 11), 0);

  Mat bw;
  cvtColor(blurred, bw, COLOR_BGR2GRAY);

  Mat edges;
  Canny(input, edges, vA, vB, vC, false);

  return edges;
};

Mat splitMat(Mat inputA, Mat inputB) {

  Rect mask = Rect(inputA.cols / 2, 0, inputA.cols / 2, inputA.rows);

  cv::copyTo(inputA, inputB, {inputA.cols / 2, 0});

  return inputA;
}

#endif
