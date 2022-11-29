/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: tested on Luogu
 */
#pragma once

template<class T> struct FT {
  vc<T> s;
  FT(int n): s(n) {}
  void update(int p, T v) {
    for (; p < sz(s); p |= p + 1) s[p] += v;
  }
  T query(int p) {
    T res = 0;
    for (; p > 0; p &= p - 1) res += s[p - 1];
    return res;
  } 
	/// start-hash
  int lower_bound(T sum) {// min pos st sum of [0, pos] >= sum
	// Returns n if no sum is >= sum, or -1 if empty sum is.
    if (sum <= 0) return -1;
    int p = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (p + pw <= sz(s) && s[p + pw - 1] < sum)
        p += pw, sum -= s[p - 1];
    }
    return p;
  } /// end-hash
};
