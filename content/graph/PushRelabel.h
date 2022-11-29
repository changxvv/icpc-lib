/**
 * Author: Simon Lindholm
 * Date: 2015-02-24
 * License: CC0
 * Source: Wikipedia, tinyKACTL
 * Description: Push-relabel using the highest label selection rule and the gap heuristic. Quite fast in practice.
 *  To obtain the actual flow, look at positive values only.
 * Time: $O(V^2\sqrt E)$
 * Status: Tested on Kattis and SPOJ, and stress-tested
 */
#pragma once

struct PushRelabel {
  struct Edge {
    int v, rev;
    ll f, c;
  };
  vc<vc<Edge>> g;
  vc<int> h, gap;
  vc<ll> ec;
  vc<vc<int>> hv;
  vc<Edge*> cur;
  PushRelabel(int n):
    g(n), ec(n), h(n), cur(n), hv(n * 2), gap(n * 2) {}
  void addEdge(int x, int y, ll c, ll rc = 0) {
    if (x == y) return;
    Edge a{y, sz(g[y]), 0, c}, b{x, sz(g[x]), 0, rc};
    g[x].emplace_back(a);
    g[y].emplace_back(b);
  }
  void addFlow(Edge &e, ll f) {
    Edge &re = g[e.v][e.rev];
    if (!ec[e.v] && f) hv[h[e.v]].emplace_back(e.v);
    e.f += f, e.c -= f, ec[e.v] += f;
    re.f -= f, re.c += f, ec[re.v] -= f;
  }
  ll maxFlow(int S, int T) {
    int n = sz(g);
    h[S] = n, ec[T] = 1, gap[0] = n - 1;
    for (int i = 0; i < n; ++i) cur[i] = g[i].data();
    for (auto &e: g[S]) addFlow(e, e.c);
    if (hv[0].empty()) return 0;
    for (int h_now = 0; h_now >= 0; ) {
      int u = hv[h_now].back();
      hv[h_now].pop_back();
      while (ec[u] > 0) {
        if (cur[u] == g[u].data() + sz(g[u])) {
          h[u] = numeric_limits<int>::max();
          for (auto &e : g[u]) {
            if (e.c && h[u] > h[e.v] + 1) {
              h[u] = h[e.v] + 1;
              cur[u] = &e;
            }
          }
          ++gap[h[u]];
          if(!--gap[h_now] && h_now < n) {
            for (int i = 0; i < n; ++i) {
              if(h_now < h[i] && h[i] < n) {
                --gap[h[i]];
                h[i] = n + 1;
              }
            }
          }
          h_now = h[u];
        } else if (cur[u]->c && h[u] == h[cur[u]->v] + 1) {
          addFlow(*cur[u], min(ec[u], cur[u]->c));
        } else ++cur[u];
      }
      while (h_now >= 0 && hv[h_now].empty()) --h_now;
    }
    return -ec[S];
  }
  bool leftOfMinCut (int a) { return h[a] >= sz(g); }
};
