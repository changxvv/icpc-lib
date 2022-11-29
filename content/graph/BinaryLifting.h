/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Calculate power of two jumps in a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Usage: auto jmp = treeJump(par); lca(jmp, dep, a, b);
 * Time: construction $O(N \log N)$, queries $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp
 */
#pragma once

auto treeJump = [](vc<int> &a) {
  int d = 32 - __builtin_clz(sz(a));
  vc<vc<int>> jmp(d, a);
  for (int i = 1; i < d; ++i) for (int j = 0; j < sz(a); ++j)
    jmp[i][j] = jmp[i - 1][jmp[i - 1][j]];
  return jmp;
};
auto lca = [](vc<vc<int>> &tbl, vc<int> &dep, int a, int b) {
  if (dep[a] < dep[b]) swap(a, b);
  auto jmp = [&](int nod, int h) {
    for (int i = 0; i < sz(tbl); ++i) if (h & (1 << i))
      nod = tbl[i][nod];
    return nod;
  };
  a = jmp(a, dep[a] - dep[b]);
  if (a == b) return a;
  for (int i = sz(tbl); i--; ) {
    int c = tbl[i][a], d = tbl[i][b];
    if (c != d) a = c, b = d;
  }
  return tbl[0][a];
};
