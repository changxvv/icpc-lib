/**
 * Author: chilli
 * Date: 2019-04-25
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: Higher precision FFT, can be used for convolutions modulo arbitrary integers
 * as long as $N\log_2N\cdot \text{mod} < 8.6 \cdot 10^{14}$ (in practice $10^{16}$ or higher).
 * Inputs must be in $[0, \text{mod})$.
 * Time: O(N \log N), where $N = |A|+|B|$ (twice as slow as NTT or FFT)
 * Status: stress-tested
 * Details: An in-depth examination of precision for both FFT and FFTMod can be found
 * here (https://github.com/simonlindholm/fft-precision/blob/master/fft-precision.md)
 */
#pragma once

#include "FastFourierTransform.h"

auto convMod = [&](vc<int> &a, vc<int> &b, int M) {
  if (a.empty() || b.empty()) return vc<ll>();
  vc<ll> res(sz(a) + sz(b) - 1);
  int B=32-__builtin_clz(sz(res)),n=1<<B, cut = int(sqrt(M));
  vc<C> L(n), R(n), outs(n), outl(n);
  for (int i = 0; i < sz(a); ++i) L[i] = C(a[i]/cut, a[i]%cut);
  for (int i = 0; i < sz(b); ++i) R[i] = C(b[i]/cut, b[i]%cut);
  fft(L), fft(R);
  for (int i = 0; i < n; ++i) {
    int j = -i & (n - 1);
    outl[j] = (L[i] + conj(L[j])) * R[i] / (n * 2.);
    outs[j] = (L[i] - conj(L[j])) * R[i] / (n * 2.) / 1i;
  }
  fft(outl), fft(outs);
  for (int i = 0; i < sz(res); ++i) {
    ll av = ll(real(outl[i]) + .5),cv = ll(imag(outs[i]) + .5),
       bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
    res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
  }
  return res;
};
