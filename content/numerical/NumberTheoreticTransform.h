/**
 * Author: chilli
 * Date: 2019-04-16
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$.
 * N must be a power of 2.
 * Useful for convolution modulo specific nice primes of the form $2^a b+1$,
 * where the convolution result has size at most $2^a$. For arbitrary modulo, see FFTMod.
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For manual convolution: NTT the inputs, multiply
   pointwise, divide by n, reverse(start+1, end), NTT back.
 * Inputs must be in [0, mod).
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/ModPow.h"

constexpr ll md = 998244353, root = 62;
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
auto ntt = [&](vc<Mod> &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vc<Mod> rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, ++s) {
    rt.resize(n);
    array<Mod, 2> z{1, mdPow(root, md >> s)};
    for (int i = k; i < k * 2; ++i) 
      rt[i] = rt[i / 2] * z[i & 1];
  }
  vc<int> rev(n);
  for (int i = 0; i < n; ++i)
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; ++i)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2) 
    for (int i = 0 ; i < n; i += k * 2) {
      auto it1 = &a[i], it2 = it1 + k;
      for (int j = 0; j < k; ++j, ++it1, ++it2) {
        Mod z = rt[j + k] * *it2;
        *it2 = *it1 - z, *it1 += z;
      }
    }
}; //7c5a0cf5
auto conv = [&](vc<Mod> a, vc<Mod> b) -> vc<Mod> {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, 
      n = 1 << (32 - __builtin_clz(s - 1));
  Mod inv = md - (md - 1) / n;
  vc<Mod> L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  for (int i = 0; i < n; ++i)
    out[-i & (n - 1)] = L[i] * R[i] * inv;
  ntt(out);
  return {out.begin(), out.begin() + s};
}; //75d60f42
