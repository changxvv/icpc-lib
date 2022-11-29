/**
 * Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid int.)
 * Status: Works fine, used a lot
 */
#pragma once

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T> struct Point {
  using P = Point;
  T x, y;
  explicit Point(T x = 0, T y = 0): x(x), y(y) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator + (P p) { return P(x + p.x, y + p.y); }
  P operator - (P p) { return P(x - p.x, y - p.y); }
  P operator * (T d) { return P(x * d, y * d); }
  P operator / (T d) { return P(x / d, y / d); }
  T dot(P p) { return x * p.x + y * p.y; }
  T cross(P p) { return x * p.y - y * p.x; }
  T cross(P a, P b) { return (a - *this).cross(b - *this); }
  T dist2() { return x * x + y * y; }
  double dist() { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() { return atan2(y, x); }
  P unit() { return * this / dist(); } // make dist() = 1
  P perp() { return P(-y, x); } // rotates +90 degrees
  P norm() { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) {
    return P(x * cos(a) - y * sin(a),x * sin(a) + y * cos(a));
  }
  friend ostream &operator<<(ostream &os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};
