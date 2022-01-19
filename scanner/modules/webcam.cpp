#include "webcam.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

VideoCapture createWebcam(int index) {
  // Open the default video camera
  VideoCapture cap;

  cap.open(index);

  // if not success, exit program
  if (cap.isOpened() == false) {
    cout << "Cannot open the video camera" << endl;
    cin.get(); // wait for any key press
    exit(0);
  }

  double dWidth =
      cap.get(CAP_PROP_FRAME_WIDTH); // get the width of frames of the video
  double dHeight =
      cap.get(CAP_PROP_FRAME_HEIGHT); // get the height of frames of the video

  cap.set(CAP_PROP_AUTO_EXPOSURE, 1);

  cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

  return cap;
}
