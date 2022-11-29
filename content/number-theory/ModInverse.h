/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * Description: Pre-computation of modular inverses. Assumes LIM $\le$ mod and that mod is a prime.
 * Time: O(n)
 * Status: Works
 */
#pragma once

constexpr ll md = 1e9 + 7, LIM = 2e4 + 1; // change this
auto mdInv = [&] {
  vc<ll> inv(LIM); inv[1] = 1;
  for (int i = 2; i < LIM; ++i) 
    inv[i] = md - (md / i) * inv[md % i] % md;
  return inv;
};
