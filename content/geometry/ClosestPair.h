/**
 * Author: Simon Lindholm
 * Date: 2019-04-17
 * License: CC0
 * Source: https://codeforces.com/blog/entry/58747
 * Description: Finds the closest pair of points.
 * Time: O(n \log n)
 * Status: Tested on Luogu
 */
#pragma once

#include "Point.h"

using P = Point<double>;
auto closest = [](vc<P> v) {
  assert(sz(v) > 1);
  set<P> S;
  sort(all(v), [](P a, P b) { return a.y < b.y; });
  pair<ll,pair<P, P>> ret{numeric_limits<ll>::max(),{P(),P()}};
  int j = 0;
  for (P p: v) {
    P d(1 + sqrt(ret.first), 0);
    while (v[j].y <= p.y - d.x) S.erase(v[j++]);
    auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
    for (; lo != hi; ++lo)
      ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
    S.insert(p);
  }
  return ret.second;
}; // 4e29a1c8
