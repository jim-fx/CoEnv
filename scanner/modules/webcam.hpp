#ifndef WEBCAM_H
#define WEBCAM_H

#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <raspicam/raspicam_cv.h>
using namespace cv;

class Camera {
private:
  raspicam::RaspiCam_Cv picam;
  VideoCapture webcam;

public:
  bool capture(Mat);
  void createCamera(int, bool);
};

#endif
