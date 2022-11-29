/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

#include "../various/BumpAllocator.h"

constexpr int INF = numeric_limits<int>::max() / 2;
struct Seg {
	Seg *ls = 0, *rs = 0;
	int l, r, mset = INF, madd = 0, val = -INF;
	Seg(int l,int r): l(l), r(r){}
	Seg(vc<int> &v, int l, int r): l(l), r(r) {
		if (l + 1 < r) {
			int mi = l + (r - l)/2;
			ls = new Seg(v, l, mi), rs = new Seg(v, mi, r);
      pull();
		} else val = v[l];
	} // 972dfe1b
  void pull() { val = max(ls->val, rs->val); }
	void push() {
		if (!ls) {
			int mi = l + (r - l)/2;
			ls = new Seg(l, mi), rs = new Seg(mi, r);
		}
		if (mset != INF)
			ls->set(l,r,mset), rs->set(l,r,mset), mset = INF;
		else if (madd)
			ls->add(l,r,madd), rs->add(l,r,madd), madd = 0;
	}
	int query(int L, int R) {
		if (R <= l || r <= L) return -INF;
		if (L <= l && r <= R) return val;
		push();
		return max(ls->query(L, R), rs->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= l || r <= L) return;
		if (L <= l && r <= R) mset = val = x, madd = 0;
		else {
			push();
      ls->set(L, R, x), rs->set(L, R, x);
      pull();
		}
	}
	void add(int L, int R, int x) {
		if (R <= l || r <= L) return;
		if (L <= l && r <= R) {
			if (mset != INF) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push();
      ls->add(L, R, x), rs->add(L, R, x);
      pull();
		}
	}
};
