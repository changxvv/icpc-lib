/**
 * Author: Changxv
 * Date: 2021-08-19
 * License: CC0
 * Description: Polynomial floor division. No leading 0's.
 * Time: O(n \log n)
 * Status: Luogu
 */

#pragma once

#include "NumberTheoreticTransform.h"

auto polyDiv = [&](vc<Mod> a, vc<Mod> b) 
               -> pair<vc<Mod>, vc<Mod>> {
  if (sz(a) < sz(b)) return {vc<Mod>(), a};
  int n = sz(a) - sz(b) + 1;
  vc<Mod> da(a.rbegin(), a.rend()), db(b.rbegin(), b.rend());
  da.resize(n), db.resize(n);
  da = conv(da, polyInv(db));
  da.resize(n), reverse(all(da));
  auto c = conv(da, b);
  a.resize(sz(b) - 1);
  for (int i = 0; i < sz(a); ++i) a[i] -= c[i];
  return {da, a};
};
