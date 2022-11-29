/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

#include "Euclid.h"

constexpr ll md = 998244353; // change to something else
struct Mod {
  ll x;
  Mod(ll x = 0): x(x) {}
  Mod operator+(Mod b) {ll y=x+b.x;return y<md ? y : y - md; }
  Mod operator-(Mod b) { return x - b.x + (x < b.x ? md : 0); }
  Mod operator * (Mod b) { return x * b.x % md; }
  Mod operator / (Mod b) { return *this * inv(b); }
  void operator += (Mod b) { x += b.x; x < md ?: x -= md; }
  void operator *= (Mod b) { (x *= b.x) %= md; }
  void operator -= (Mod b) { x -= b.x; -x < 0 ?: x += md; }
  void operator /= (Mod b) { *this *= inv(b); }
  Mod inv(Mod a) {
    ll x, y, g = euclid(a.x, md, x, y);
    assert(g == 1); 
    return (x + md) % md;
  }
  Mod operator ^ (ll e) {
    if (!e) return 1;
    Mod r = *this ^ (e / 2); r = r * r;
    return e & 1 ? *this * r : r;
  }
  friend ostream &operator << (ostream &os, Mod m) {
    return os << m.x;
  }
};
