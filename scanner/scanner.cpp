#include "modules/filter.hpp"
#include "modules/webcam.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
  VideoCapture cam = createWebcam();

  string window_name = "CameraStream";
  namedWindow(window_name);

  while (true) {
    Mat frame;
    bool bSuccess = cam.read(frame);

    if (bSuccess == false) {
      cout << "Video camera is disconnected" << endl;
      cin.get(); // Wait for any key press
      break;
    }

    Mat filteredMat = filterCanny(frame);

    Mat output = splitMat(frame, filteredMat);

    waitKey(10);
    imshow(window_name, filteredMat);
  }

  return 0;
}
