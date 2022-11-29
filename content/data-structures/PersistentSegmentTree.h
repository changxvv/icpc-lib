/**
 * Author: Changxv
 * Date: 2020-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with persistent ability. Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = null; tr->insert(-INF, INF, pos, val);
 * Status: tested on Luogu
 */
#pragma once

#include "../various/BumpAllocator.h"

struct Seg {
  static Seg *null;
  Seg *ls = this, *rs = this;
  int val = 0;
  Seg() {}
  Seg(int val): ls(null), rs(null), val(val) {}
  Seg(Seg *ls, Seg *rs): ls(ls), rs(rs) {
    val += ls->val;
    val += rs->val;
  }
  Seg *insert(int l, int r, int pos, int v) {
    if (pos < l || pos >= r) return this;
    if (l + 1 == r) return new Seg(val + v);
    int mi = l + (r - l) / 2;
    return new Seg(ls->insert(l, mi, pos, v), 
                   rs->insert(mi, r, pos, v));
  }
  int query(Seg *p, int l, int r, int k) {
    if (l + 1 == r) return l;
    int mi = l + (r - l) / 2, cnt = ls->val - p->ls->val;
    return cnt >= k ? ls->query(p->ls, l, mi, k) : 
                      rs->query(p->rs, mi, r, k - cnt);
  }
};
Seg *Seg::null = new Seg;
