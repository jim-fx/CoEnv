#ifndef WEBCAM_H
#define WEBCAM_H

#include "opencv2/opencv.hpp"
using namespace cv;

class Camera {
public:
  bool capture(Mat output);
  void createCamera(int index, bool isPi);
};

#endif
