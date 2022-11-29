/**
 * Author: Me
 * Date: Unknown
 * Source: Local
 * Description: Min-cost max-flow. Note that negative cost cycles are not supported.
 * Status: Tested on Luogu 
 * Time: Approximately O(E^2)
 */
#pragma once

// #include <bits/extc++.h> /// include-line, keep-include

constexpr ll INF = numeric_limits<ll>::max() / 2;

struct MCMF {
  struct Edge {
    int v, back;
    ll f, c;
  };
  int s, t;
  vc<vc<Edge>> g;
  vc<ll> dis, p;
  vc<int> vis;
  MCMF(int n): g(n), dis(n), p(n), vis(n) {}
  void add_edge(int x, int y, ll f, ll c) {
    Edge a{y, sz(g[y]), f, c}, b{x, sz(g[x]), 0, -c};
    g[x].emplace_back(a);
    g[y].emplace_back(b);
  };
  bool setpi() {
    queue<int> Q;
    fill(all(dis), INF);
    dis[t] = 0;
    Q.emplace(t);
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      vis[u] = 0;
      for (auto e: g[u]) {
        auto re = g[e.v][e.back];
        if (re.f && dis[e.v] > dis[u] + re.c) {
          dis[e.v] = dis[u] + re.c;
          if (!vis[e.v]) {
            vis[e.v] = 1;
            Q.emplace(e.v);
          }
        }
      }
    }
    return dis[s] != INF;
  }
  bool path() {
    fill(all(dis), INF);
    __gnu_pbds::priority_queue<pair<ll, int>> Q;
    vc<decltype(Q)::point_iterator> it(sz(p));
    dis[t] = 0;
    it[t] = Q.push({-dis[t], t});
    while (!Q.empty()) {
      int u = Q.top().second;
      Q.pop();
      for (auto e: g[u]) {
        auto re = g[e.v][e.back];
        if (re.f && dis[e.v] > dis[u] + re.c) {
          dis[e.v] = dis[u] + re.c;
          if (it[e.v] == Q.end())
            it[e.v] = Q.push({-dis[e.v], e.v});
          else Q.modify(it[e.v], {-dis[e.v], e.v}); 
        }
      }
    }
    return dis[s] != INF;
  }
  ll dfs(int u, ll flow) {
    if (u == t || !flow) return flow;
    vis[u] = 1;
    ll w = flow;
    for (auto &e: g[u]) 
      if (e.f && !vis[e.v] && !e.c) {
        ll tmp = dfs(e.v, min(e.f, w));
        w -= tmp, e.f -= tmp, g[e.v][e.back].f += tmp;
        if (!w) return flow;
      }
    return flow - w;
  }
  pair<ll, ll> mincost_flow(int S, int T) {
    s = S, t = T;
    if (!setpi()) return {};
    ll flow = 0, cost = 0, delta = 0, tmp;
    do {
      for (int u = 0; u < sz(g); ++u)
        for (auto &e: g[u]) e.c += dis[e.v] - dis[u];
      delta += dis[s];
      do {
        fill(all(vis), 0);
        tmp = dfs(s, INF);
        flow += tmp, cost += tmp * delta;
      }while (tmp);
    }while (path());
    return {flow, cost};
  }
};