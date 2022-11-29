/**
 * Author: Simon Lindholm
 * Date: 2015-01-31
 * License: CC0
 * Source: me
 * Description: A class for ordering angles (as represented by int points and
 *  a number of rotations around the origin). Useful for rotational sweeping.
 *  Sometimes also represents points or vectors.
 * Usage:
 *  vector<Angle> v = {w[0], w[0].t360() ...}; // sorted
 *  int j = 0; rep(i,0,n) { while (v[j] < v[i].t180()) ++j; }
 *  // sweeps j such that (j-i) represents the number of positively oriented triangles with vertices at 0 and i
 * Status: Used, works well
 */
#pragma once

struct Angle {
	ll x, y;
  int t;
	Angle(ll x, ll y, int t = 0): x(x), y(y), t(t) {}
	int half() const {
		assert(x || y);
		return y < 0 || (y == 0 && x < 0);
	}
	Angle t90() const { return {-y, x, t + (half() && x >= 0)}; }
	Angle t180() const { return {-x, -y, t + half()}; }
	Angle t360() const { return {x, y, t + 1}; }
  bool operator < (Angle r) const {
	// add a.dist2() and b.dist2() to also compare distances
    return make_tuple(t, half(), y * r.x) < 
           make_tuple(r.t, r.half(), x * r.y);
  }
  Angle operator + (Angle r) { // + vector r
    Angle c(x + r.x, y + r.y, t);
    if (t180() < c) --c.t;
    return c.t180() < *this ? c.t360() : c;
  }
  Angle operator - (Angle r) { // - angle r
    int tt = t - r.t; r.t = t;
    return {x * r.x + y * r.y, y * r.x - x * r.y, tt - (*this < r)};
  }
};

// Given two points, this calculates the smallest angle between
// them, i.e., the angle that covers the defined line segment.
array<Angle, 2> segmentAngles(Angle a, Angle b) {
	if (b < a) swap(a, b);
  if (b < a.t180()) return {a, b};
  return {b, a.t360()};
}
