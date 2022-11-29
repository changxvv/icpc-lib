/**
 * Author: Changxv
 * Date: 2021-08-19
 * License: CC0
 * Description: Compute the $A^m\pmod{x^n}$, where the A is a polynomial and n is the size of A.
 * Notice that you should change the constant term of the PolyExp.
 * Time: O(n \log n)
 * Status: Check Library
 */

#pragma once

#include "PolyLn.h"
#include "PolyExp.h"

auto polyPow = [&](vc<Mod> &a, ll k) {
  int n = sz(a), t = n;
  for (int i = 0; i < n; ++i) if (a[i].x) { t = i; break; }
  if (t * k >= n) return vc<Mod>(n, 0);
  vc<Mod> b(a.begin() + t, a.end());
  b.resize(n - t * k);
  Mod a0 = b[0];
  b = polyLn(b);
  ll k1 = k % md;
  for (Mod &e: b) e *= k1;
  b = polyExp(b, mdPow(a0, k % (md - 1)));
  b.insert(b.begin(), t * k, 0);
  return b;
};
