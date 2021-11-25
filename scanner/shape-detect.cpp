/**
 * Simple shape detector program.
 * It loads an image and tries to find simple shapes (rectangle, triangle,
 * circle, etc) in it. This program is a modified version of `squares.cpp` found
 * in the OpenCV sample dir.
 */
#include "opencv2/calib3d.hpp"
#include "opencv2/core/utility.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <modules/webcam.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

/**
 * Helper function to find a cosine of angle between vectors
 * from pt0->pt1 and pt0->pt2
 */
static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
  double dx1 = pt1.x - pt0.x;
  double dy1 = pt1.y - pt0.y;
  double dx2 = pt2.x - pt0.x;
  double dy2 = pt2.y - pt0.y;
  return (dx1 * dx2 + dy1 * dy2) /
         sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
}

/**
 * Helper function to display text in the center of a contour
 */
void setLabel(cv::Mat &im, const std::string label,
              std::vector<cv::Point> &contour) {
  int fontface = cv::FONT_HERSHEY_SIMPLEX;
  double scale = 0.4;
  int thickness = 1;
  int baseline = 0;

  cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
  cv::Rect r = cv::boundingRect(contour);

  cv::Point pt(r.x + ((r.width - text.width) / 2),
               r.y + ((r.height + text.height) / 2));
  cv::rectangle(im, pt + cv::Point(0, baseline),
                pt + cv::Point(text.width, -text.height), CV_RGB(255, 255, 255),
                cv::FILLED);
  cv::putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

Scalar ScalarHSV2BGR(uchar H, uchar S, uchar V) {
  Mat rgb;
  Mat hsv(1, 1, CV_8UC3, Scalar(H, S, V));
  cvtColor(hsv, rgb, cv::COLOR_HSV2BGR);
  return Scalar(rgb.data[0], rgb.data[1], rgb.data[2]);
}

bool compareAreas(std::vector<cv::Point> a, std::vector<cv::Point> b) {
  return contourArea(a) > contourArea(b);
}

bool compareXCords(Point p1, Point p2) { return (p1.x < p2.x); }

bool compareYCords(Point p1, Point p2) { return (p1.y < p2.y); }

bool compareDistance(std::pair<Point, Point> p1, std::pair<Point, Point> p2) {
  return (norm(p1.first - p1.second) < norm(p2.first - p2.second));
}

void orderPoints(std::vector<cv::Point> inpts,
                 std::vector<cv::Point> &ordered) {
  sort(inpts.begin(), inpts.end(), compareXCords);
  std::vector<Point> lm(inpts.begin(), inpts.begin() + 2);
  std::vector<Point> rm(inpts.end() - 2, inpts.end());

  sort(lm.begin(), lm.end(), compareYCords);
  Point tl(lm[0]);
  Point bl(lm[1]);
  std::vector<std::pair<Point, Point>> tmp;
  for (size_t i = 0; i < rm.size(); i++) {
    tmp.push_back(std::make_pair(tl, rm[i]));
  }

  sort(tmp.begin(), tmp.end(), compareDistance);
  Point tr(tmp[0].second);
  Point br(tmp[1].second);

  ordered.push_back(tl);
  ordered.push_back(tr);
  ordered.push_back(br);
  ordered.push_back(bl);
}
double _distance(Point p1, Point p2) {
  return sqrt(((p1.x - p2.x) * (p1.x - p2.x)) +
              ((p1.y - p2.y) * (p1.y - p2.y)));
}

void fourPointTransform(Mat src, Mat &dst, std::vector<Point> pts) {
  std::vector<Point> ordered_pts = pts;

  double wa = _distance(ordered_pts[2], ordered_pts[3]);
  double wb = _distance(ordered_pts[1], ordered_pts[0]);
  double mw = max(wa, wb);

  double ha = _distance(ordered_pts[1], ordered_pts[2]);
  double hb = _distance(ordered_pts[0], ordered_pts[3]);
  double mh = max(ha, hb);

  Point2f src_[] = {
      Point2f(ordered_pts[0].x, ordered_pts[0].y),
      Point2f(ordered_pts[1].x, ordered_pts[1].y),
      Point2f(ordered_pts[2].x, ordered_pts[2].y),
      Point2f(ordered_pts[3].x, ordered_pts[3].y),
  };

 if (mw > mh) {
    src_[0] = Point2f(ordered_pts[3].x, ordered_pts[3].y);
    src_[1] = Point2f(ordered_pts[0].x, ordered_pts[0].y);
    src_[2] = Point2f(ordered_pts[1].x, ordered_pts[1].y);
    src_[3] = Point2f(ordered_pts[2].x, ordered_pts[2].y);
  }

  float xOff = mw / 2;

  Point2f dst_[] = {Point2f(0 + xOff, 0), Point2f(mw - 1 + xOff, 0),
                    Point2f(mw - 1 + xOff, mh - 1), Point2f(0 + xOff, mh - 1)};
  Mat m = getPerspectiveTransform(src_, dst_);
  warpPerspective(src, dst, m, Size(mw * 2, mh));
}

void drawContour(std::vector<cv::Point> contour, cv::Mat dst) {
  std::vector<cv::Point> approx;

  // Approximate contour with accuracy proportional
  // to the contour perimeter
  cv::approxPolyDP(cv::Mat(contour), approx,
                   cv::arcLength(cv::Mat(contour), true) * 0.02, true);

  // Skip small or non-convex objects
  if (std::fabs(cv::contourArea(contour) < 100 ||
                !cv::isContourConvex(approx)) ||
      approx.size() != 6) {
    return;
  }

  // Get the cosines of all corners
  std::vector<double> cos;
  for (int j = 2; j < 6 + 1; j++)
    cos.push_back(angle(approx[j % 6], approx[j - 2], approx[j - 1]));

  // Sort ascending the cosine values
  std::sort(cos.begin(), cos.end());

  // Draw center
  std::vector<cv::Point> centerRect(4);

  if (_distance(approx[0], approx[1]) >= _distance(approx[1], approx[2])) {
    centerRect[0] = approx[1];
    centerRect[1] = approx[3];
    centerRect[2] = approx[4];
    centerRect[3] = approx[0];
  } else {
    centerRect[0] = approx[0];
    centerRect[1] = approx[1];
    centerRect[2] = approx[3];
    centerRect[3] = approx[4];
  }

  Mat warped_image;
  fourPointTransform(dst, warped_image, centerRect);

  Mat warped_image_size;

  resize(warped_image, warped_image_size, Size(200, 200), 0, 0, INTER_CUBIC);

  Mat warped_image_grey;
  cvtColor(warped_image_size, warped_image_grey, cv::COLOR_BGR2GRAY);

  Mat warped_image_thresh;
  threshold(warped_image_grey, warped_image_thresh, 100, 255, THRESH_BINARY);

  imshow("Warped Image", warped_image_thresh);

  polylines(dst, centerRect, true, Scalar(120, 120, 120), 1, 150, 0);

  for (int x = 0; x < 6; x++) {
    Point p = approx[x];
    cv::circle(dst, p, 4 + x, ScalarHSV2BGR(x * 20, 120, 200), 5);
  }
}

void detectShape(cv::Mat src) {
  // Convert to grayscale
  cv::Mat gray;
  cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

  // Use Canny instead of threshold to catch squares with gradient shading
  cv::Mat bw;
  cv::Canny(gray, bw, 0, 50, 5);

  // Find contours
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(bw.clone(), contours, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_SIMPLE);

  std::sort(contours.begin(), contours.end(), compareAreas);

  if (contours.size() > 0) {
    drawContour(contours[0], src);
  }

  cv::imshow("dst", src);
  cv::waitKey(10);
}

int main() {
  VideoCapture cam = createWebcam(2);

  while (true) {
    cv::Mat frame;

    if (cam.read(frame) == true) {
      detectShape(frame);
    }
  }
  return 0;
}
