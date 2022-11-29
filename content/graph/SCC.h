/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

int tim = 0;
vc<int> low(n), comp(n, -1), st, topo;
function<int(int)> dfs = [&](int u) {
	int lw = low[u] = ++tim, x; 
	st.emplace_back(u);
	for (int v: g[u]) if (comp[v] < 0)
		lw = min(lw, low[v] ?: dfs(v));

	if (lw == low[u]) {
		topo.emplace_back(u);
		do {
			comp[x = st.back()] = u;
			st.pop_back();
		} while (x != u);
	}
	return low[u] = lw;
};
auto tarjan = [&] {
	for (int i = 0; i < n; ++i) if (comp[i] < 0) dfs(i);
	reverse(all(topo));
};
