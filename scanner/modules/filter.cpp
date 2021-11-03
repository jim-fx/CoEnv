#ifndef FILTER_H
#define FILTER_H

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

Mat filterCanny(Mat input) {

  Mat blurred;
  GaussianBlur(input, blurred, Size(11, 11), 0);

  Mat bw;
  cvtColor(blurred, bw, COLOR_BGR2GRAY);

  Mat edges;
  Canny(input, edges, 100, 200, 7, false);

  return edges;
};

Mat splitMat(Mat inputA, Mat inputB) {

  Rect mask = Rect(inputA.cols / 2, 0, inputA.cols / 2, inputA.rows);

  // inputB(mask).copyTo(inputA, [ inputA.cols / 2, 0 ]);

  return inputA;
}

#endif
