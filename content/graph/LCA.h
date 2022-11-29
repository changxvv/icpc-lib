/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). g should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCA {
  int T = 0;
  vc<int> tim, pth, ret;
  RMQ<int> rmq;
  LCA(vc<vc<int>> &g): tim(sz(g)), rmq((dfs(g, 0, -1), ret)) {}
  void dfs(vc<vc<int>> &g, int u, int p) {
    tim[u] = T++;
    for (int v: g[u]) if (v != p) {
      pth.emplace_back(u), ret.emplace_back(tim[u]);
      dfs(g, v, u);
    }
  }
  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax(tim[a], tim[b]);
    return pth[rmq.query(a, b)];
  }
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};
