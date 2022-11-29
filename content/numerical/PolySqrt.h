/**
 * Author: Changxv
 * Date: 2021-08-18
 * License: CC0
 * Description: Compute the sqrt of a, where a is a polynomial 
 * and a[0] = 1(if not, ModSqrt is required).
 * Time: O(n \log n)
 * Status: Luogu
 */

#pragma once

#include "PolyInverse.h"

auto polySqrt = [&](vc<Mod> &a) -> vc<Mod> {
  if (a.empty()) return {};
  vc<Mod> b{1}, ib{1};
  b.reserve(sz(a)), ib.reserve(sz(a));
  auto conv = [&](vc<Mod> &a, vc<Mod> &b) {
    ntt(a);
    for (int i = 0; i < sz(a); ++i) a[i] *= b[i];
    ntt(a), reverse(a.begin() + 1, a.end());
  };
  while (sz(b) < sz(a)) {
    int h = sz(b), n = h * 2;
    vc<Mod> in(n), out(n);
    copy(all(ib), in.begin()), ntt(in);
    copy(all(b), out.begin());
    conv(out, out), fill(out.begin(), out.begin() + h, 0);
    Mod inv = md - (md - 1) / n;
    for (int i = h; i < min(n, sz(a)); ++i)
      out[i] = out[i] * inv - a[i];
    conv(out, in), b.resize(n), inv *= (md / 2);
    for (int i = h; i < n; ++i) b[i] = out[i] * inv;
    if (sz(b) < sz(a)) invIter(b, in, ib);
  }
  return {b.begin(), b.begin() + sz(a)};
};
