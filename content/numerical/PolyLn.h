/**
 * Author: Changxv
 * Date: 2021-08-19
 * License: CC0
 * Description: Compute the Ln of a, where a is a polynomial 
 * and a[0] = 1.
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
auto inte = [&](vc<Mod> a) {
  for (int i = sz(a) - 1; i >= 1; --i)
    a[i] = a[i - 1] * iv[i];
  a[0] = 0;
  return a;
};
auto polyLn = [&](vc<Mod> &a) -> vc<Mod> {
  if (a.empty()) return {};
  int n = 1 << (32 - __builtin_clz(2 * sz(a) - 2));
  Mod inv = md - (md - 1) / n;
  vc<Mod> b = polyInv(a), c = deri(a);
  b.resize(n), c.resize(n);
  ntt(b), ntt(c);
  for (int i = 0; i < n; ++i) b[i] = b[i] * c[i] * inv;
  ntt(b), reverse(b.begin() + 1, b.end());
  b = inte(b);
  return {b.begin(), b.begin() + sz(a)};
};
