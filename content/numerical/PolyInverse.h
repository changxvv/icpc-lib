/**
 * Author: Changxv
 * Date: 2021-08-18
 * License: CC0
 * Description: Compute the inversion of the Polynomial.
 * Time: O(n \log n)
 * Status: Luogu
 */

#pragma once

#include "NumberTheoreticTransform.h"

auto invIter = [&](vc<Mod> &a, vc<Mod> &in, vc<Mod> &b) {
  int n = sz(in);
  vc<Mod> out(n);
  copy(a.begin(), a.begin() + min(sz(a), n), out.begin());
  auto conv = [&] {
    ntt(out);
    for (int i = 0; i < n; ++i) out[i] *= in[i];
    ntt(out), reverse(out.begin() + 1, out.end());
  };
  conv(), fill(out.begin(), out.begin() + sz(b), 0), conv();
  b.resize(n);
  Mod inv = md - (md - 1) / n; inv *= inv;
  for (int i = n / 2; i < n; ++i)
    b[i] = out[i].x ? inv * (md - out[i].x) : 0;
}; //787b29bc
auto polyInv = [&](vc<Mod> &a) -> vc<Mod> {
  if (a.empty()) return {};
  vc<Mod> b{mdPow(a[0], md - 2)};
  b.reserve(sz(a));
  while (sz(b) < sz(a)) {
    vc<Mod> in(sz(b) * 2); 
    copy(all(b), in.begin()), ntt(in);
    invIter(a, in, b);
  }
  return {b.begin(), b.begin() + sz(a)};
};
