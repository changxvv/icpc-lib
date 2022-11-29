/**
 * Author: Changxv
 * Date: 2021-08-19
 * License: CC0
 * Description: Compute the Exp of a, where a is a polynomial 
 * and a[0] = 0.
 * Time: O(n \log n)
 * Status: Luogu
 */

#pragma once

#include "PolyInverse.h"
#include "../number-theory/ModInverse.h"

auto deri = [&](vc<Mod> a) {
  for (int i = 1; i < sz(a); ++i) a[i - 1] = a[i] * i;
  a.pop_back();
  return a;
};
auto polyExp = [&](vc<Mod> &a) -> vc<Mod> {
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
    Mod inv = md - (md - 1) / n;
    vc<Mod> db(n), dib(n), A(deri(b)), B(n);
    copy(all(ib), dib.begin()), ntt(dib);
    copy(all(b), db.begin()), ntt(db);
    A.resize(n), conv(A, dib);
    for (int i = 0; i < n; ++i) B[i] = db[i] * dib[i];
    ntt(B), reverse(B.begin() + 1, B.end());
    fill(B.begin(), B.begin() + h, 0);
    vc<Mod> da(deri(vc<Mod>(a.begin(), a.begin() + h)));
    da.resize(n), ntt(da), conv(B, da);
    for (int i = min(n, sz(a)) - 1; i >= h; --i)
      A[i] = (A[i - 1] - B[i - 1] * inv) * iv[i] * inv - a[i];
    fill(A.begin(), A.begin() + h, 0), conv(A, db);
    b.resize(n);
    for (int i = h; i < n; ++i) 
      b[i] = A[i].x ? inv * (md - A[i].x) : 0;
    if (sz(b) < sz(a)) invIter(b, dib, ib);
  }
  return {b.begin(), b.begin() + sz(a)};
};
