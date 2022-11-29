/**
 * Author: Simon Lindholm
 * Date: 2015-09-01
 * License: CC0
 * Description: Computes the pair of points at which two circles intersect. Returns false in case of no intersection. Assert if inf intersections.
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

template<class P>
bool circleInter(P a,P b,double r1,double r2,array<P, 2>&out) {
	if (a == b) { assert(r1 != r2); return 0; }
	P vec = b - a;
	double d2 = vec.dist2(), sum = r1 + r2, dif = r1 - r2,
	       p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
	if (sum * sum < d2 || dif * dif > d2) return 0;
	P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
	out = {mid + per, mid - per};
	return 1;
}

