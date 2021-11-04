#include "modules/filter.hpp"
#include "modules/webcam.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int vA = 1;
int vB = 150;
int vC = 3;
float vD = 0.5;
void on_trackbar_a(int pos, void *) { vA = pos * 2; }
void on_trackbar_b(int pos, void *) { vB = pos; }
void on_trackbar_c(int state, void *) {
  vC = 3;
  if (state > 50) {
    vC = 7;
  }
}
void on_trackbar_d(int pos, void *) { vD = pos / float(100); }

bool compareAreas(vector<Point> a, vector<Point> b) {
  return contourArea(a) > contourArea(b);
}

int main(int argc, char *argv[]) {
  VideoCapture cam = createWebcam(2);

  string window_name = "CameraStream";
  string control_window = "ControlWindow";
  namedWindow(window_name);
  namedWindow(control_window);

  createTrackbar("vA", control_window, nullptr, 200, on_trackbar_a);
  createTrackbar("vB", control_window, nullptr, 200, on_trackbar_b);
  createTrackbar("3x7", control_window, nullptr, 100, on_trackbar_c);
  createTrackbar("threshold", control_window, nullptr, 100, on_trackbar_d);

  while (true) {
    Mat frame;
    bool bSuccess = cam.read(frame);

    if (bSuccess == false) {
      cout << "Video camera is disconnected" << endl;
      cin.get(); // Wait for any key press
      break;
    }

    Mat blurred;
    GaussianBlur(frame, blurred, Size(vA, vA), 0);

    Mat bw;
    cvtColor(blurred, bw, COLOR_BGR2GRAY);

    Size kernalSize(5, 5);
    Mat element = getStructuringElement(MORPH_RECT, kernalSize, Point(1, 1));
    morphologyEx(bw, bw, MORPH_CLOSE, element);

    Mat outputCanny;
    Canny(frame, outputCanny, 130, 200, vC, false);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(outputCanny.clone(), contours, hierarchy, RETR_CCOMP,
                 CHAIN_APPROX_SIMPLE);

    sort(contours.begin(), contours.end(), compareAreas);

    float sizes[contours.size()];
    float accArea = 0.0;
    float maxArea = 0.0;
    for (unsigned int i = 0; i < contours.size(); i++) {
      sizes[i] = contourArea(contours[i]);
      accArea += sizes[i];
      if (sizes[i] > maxArea) {
        maxArea = sizes[i];
      }
    }

    float averageArea = accArea / contours.size();

    RNG rng(12345);

    Mat drawing = Mat::zeros(outputCanny.size(), CV_8UC3);
    for (unsigned int i = 0; i < contours.size(); i++) {
      if (sizes[i] > maxArea * vD) {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256),
                              rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
      }
    }
    imshow("Contours", drawing);
    // imshow(window_name, frame);
    int key = waitKey(10);

    if (key == 27) {
      break;
    }
  }

  return 0;
}
