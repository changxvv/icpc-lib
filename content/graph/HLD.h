/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/SegmentTree.h"

template<bool EDGE> struct HLD {
  int n, tim = 0;
  vc<vc<int>> g;
  vc<int> par, siz, dep, rt, pos;
  Seg tr;
  HLD(vc<vc<int>> g): n(sz(g)), g(g), par(n, -1), siz(n, 1), 
                      dep(n), rt(n), pos(n), tr(n) { 
                      dfsSiz(0); dfsHld(0); }
  void dfsSiz(int u) {
    if (~par[u]) g[u].erase(find(all(g[u]), par[u]));
    for (auto &v: g[u]) {
      par[v] = u, dep[v] = dep[u] + 1;
      dfsSiz(v);
      siz[u] += siz[v];
      if (siz[v] > siz[g[u][0]]) swap(v, g[u][0]);
    }
  } //f3bc4162
  void dfsHld(int u) {
    pos[u] = tim++;
    for (auto v: g[u]) {
      rt[v] = (v == g[u][0] ? rt[u] : v);
      dfsHld(v);
    }
  } //bac86e27
  template<class F> void process(int u, int v, F op) {
    for (; rt[u] != rt[v]; v = par[rt[v]]) {
      if (dep[rt[u]] > dep[rt[v]]) swap(u, v);
      op(pos[rt[v]], pos[v] + 1);
    }
    if (dep[u] > dep[v]) swap(u, v);
    op(pos[u] + EDGE, pos[v] + 1);
  } //974632cb
  void modifyPath(int u, int v, int val) {
    process(u, v, [&](int l, int r) { tr.modify(l, r, val); });
  }
  int queryPath(int u, int v) {
    int res = 0;
    process(u, v, [&](int l, int r) { 
      (res += tr.query(l, r)) %= P; 
    });
    return res;
  }
  int querySubtree(int u) { // modifySubtree is similar
    return tr.query(pos[u] + EDGE, pos[u] + siz[u]);
  }
};
