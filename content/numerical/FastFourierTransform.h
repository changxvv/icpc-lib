/**
 * Author: Ludo Pulles, chilli, Simon Lindholm
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power of 2.
   Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
   Otherwise, use NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

using C = complex<double>;
using vd = vc<double>;

auto fft = [&](vc<C> &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vc<C> R(2, 1), rt(2, 1); // R can be long double
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n), rt.resize(n);
    auto x = polar(1., acos(-1) / k);
    for (int i = k; i < k * 2; ++i) 
      rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }
  vc<int> rev(n);
  for (int i = 0; i < n; ++i) 
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; ++i) 
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2) 
    for (int i = 0; i < n; i += k * 2) {
      auto it1 = &a[i], it2 = it1 + k;
      for (int j = 0; j < k; ++j, ++it1, ++it2) {
        auto x = (double *)&rt[j + k], y = (double *)it2;
        C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1] * y[0]);
        *it2 = *it1 - z;
        *it1 += z;
      }
    }
}; //bfe3257c
auto conv = [&](vd &a,vd &b) {
  if (a.empty() || b.empty()) return vd();
  vd res(sz(a) + sz(b) - 1);
  int L = 32 - __builtin_clz(sz(res) - 1), n = 1 << L;
  vc<C> in(n), out(n);
  copy(all(a), begin(in));
  for (int i = 0; i < sz(b); ++i) in[i].imag(b[i]);
  fft(in);
  for (C &x: in) x *= x;
  for (int i = 0; i < n; ++i) 
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  for (int i = 0; i < sz(res); ++i) 
    res[i] = imag(out[i]) / (n * 4);
  return res;
}; //13bd14b6
