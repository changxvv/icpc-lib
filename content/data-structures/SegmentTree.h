/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed segment tree. Bounds are inclusive to the left and exclusive to the right.
 * Time: O(\log N)
 * Status: Tested on Luogu
 */
#pragma once

struct Seg {
  int n, h;
  vc<int> s, add;
  Seg(int n): n(n), h(32 - __builtin_clz(n)), s(n * 2), 
              add(n) {}
  void update(int x,int v, int l) {
    s[x] += v * l;
    if (x < n) add[x] += v;
  }
  void push(int l, int r) {
    int b = h, k = 1 << (h - 1);
    for (l += n, r += n - 1; b > 0; --b, k /= 2)
      for (int x = l >> b; x <= r >> b; ++x) if (add[x]) {
        update(x * 2, add[x], k);
        update(x * 2 + 1, add[x], k);
        add[x] = 0;
      }
  }
  void pull(int l, int r) {
    int k = 2;
    for(l += n, r += n - 1; l > 1; k *= 2) {
      l /= 2, r /= 2;
      for (int x = r; x >= l; --x) {
        s[x] = s[x * 2] + s[x * 2 + 1] + add[x] * k;
      }
    }
  }
  void modify(int l, int r, int v) { /// start-hash
    push(l, l + 1);
    push(r - 1, r);
    int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l /= 2, r /= 2, k *= 2) {
      if (l & 1) update(l++, v, k);
      if (r & 1) update(--r, v, k);
    }
    pull(l0, l0 + 1);
    pull(r0 - 1, r0);
  } /// end-hash
  int query(int l, int r) {
    push(l, l + 1);
    push(r - 1, r);
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) res += s[l++];
      if (r & 1) res += s[--r];
    }
    return res;
  }
};
