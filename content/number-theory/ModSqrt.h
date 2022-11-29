/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Tonelli-Shanks algorithm for modular square roots. Finds $x$ s.t. $x^2 = a \pmod p$ ($-x$ gives the other solution). p should be an odd prime and $0 \le a < p$ .
 * Time: O(\log^2 p) worst case, O(\log p) for most $p$
 * Status: Luogu
 */
#pragma once

#include "ModPow.h"

auto mdSqrt = [&](ll a) -> ll {
  if (!a) return 0;
  if (mdPow(a, md / 2) != 1) return -1;
  if (md % 4 == 3) return mdPow(a, (md + 1) / 4);
	// a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
  ll s = md - 1, n = 2;
  int r = 0, m;
  while (s % 2 == 0) ++r, s /= 2;
  while (mdPow(n, md / 2) != md - 1) ++n;
  ll x = mdPow(a, (s + 1) / 2), b = mdPow(a, s), g = mdPow(n, s);
  for (; ; r = m) {
    ll t = b;
    for (m = 0; m < r && t != 1; ++m) (t *= t) %= md;
    if (!m) return x;
    ll gs = mdPow(g, 1ll << (r - m - 1));
    g = gs * gs % md, (x *= gs) %= md, (b *= g) %= md;
  }
};
