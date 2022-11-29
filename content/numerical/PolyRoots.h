/**
 * Author: Per Austrin
 * Date: 2004-02-08
 * License: CC0
 * Description: Finds the real roots to a polynomial.
 * Usage: polyRoots({{2,-3,1}},-1e9,1e9) // solve x^2-3x+2 = 0
 * Time: O(n^2 \log(1/\epsilon))
 */
#pragma once

#include "Polynomial.h"

vc<double> polyRoots(Poly p, double xmin, double xmax) {
	if (sz(p.a) == 2) { return {-p.a[0]/p.a[1]}; }
	vc<double> ret;
	Poly der = p;
	der.diff();
	auto dr = polyRoots(der, xmin, xmax);
	dr.emplace_back(xmin-1);
	dr.emplace_back(xmax+1);
	sort(all(dr));
  for (int i = 0; i < sz(dr) - 1; ++i) {
		double l = dr[i], h = dr[i+1];
		bool sign = p(l) > 0;
		if (sign ^ (p(h) > 0)) {
      for (int it = 0; it < 60; ++it) { // while (h - l > 1e-8)
				double m = (l + h) / 2, f = p(m);
				if ((f <= 0) ^ sign) l = m;
				else h = m;
			}
			ret.emplace_back((l + h) / 2);
		}
	}
	return ret;
}
