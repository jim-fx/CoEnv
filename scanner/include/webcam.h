#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include <raspicam/raspicam.h>
#include <raspicam/raspicam_cv.h>
#include <raspicam/raspicamtypes.h>

#include "webcam.c"

using namespace cv;

bool captureCamera(Mat &);
void createCamera(int, bool);
