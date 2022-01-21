#include <opencv2/opencv.hpp>
using namespace cv;

Point scalePointOrigin(cv::Point point, cv::Point origin, float scale) {
  return Point(((point.x - origin.x) * scale) + origin.x,
               ((point.y - origin.y) * scale) + origin.y);
}

Point rotatePointOrigin(cv::Point point, cv::Point origin, float angle) {
  float x2 = ((point.x - origin.x) * cos(angle)) -
             ((point.y - origin.y) * sin(angle)) + origin.x;
  float y2 = ((point.x - origin.x) * sin(angle)) +
             ((point.y - origin.y) * cos(angle)) + origin.y;
  return Point(x2, y2);
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

/**
 * Helper function to find a cosine of angle between vectors
 * from pt0->pt1 and pt0->pt2
 */
double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
  double dx1 = pt1.x - pt0.x;
  double dy1 = pt1.y - pt0.y;
  double dx2 = pt2.x - pt0.x;
  double dy2 = pt2.y - pt0.y;
  return (dx1 * dx2 + dy1 * dy2) /
         sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
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

bool compareDistance(std::pair<Point, Point> p1, std::pair<Point, Point> p2) {
  return (norm(p1.first - p1.second) < norm(p2.first - p2.second));
}

bool compareXCords(Point p1, Point p2) { return (p1.x < p2.x); }
bool compareYCords(Point p1, Point p2) { return (p1.y < p2.y); }
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
