/**
 * Author: PotatoHashing
 * Date: 2021-05-20
 * Source: https://github.com/kth-competitive-programming/kactl/blob/e95227d778b9f78cb5047cd60a9a3ac397c95a00/content/graph/LCT.h
 * Description: link-cut Tree. Supports BST-like augmentations. (Can be used in place of HLD).
 * Current implementation supports update value at a node, and query max on a path.
 * Time: All operations take amortized O(\log N).
 * Status: Tested on Luogu
 */
#pragma once

struct Node {
  Node *p, *pp, *c[2];
  bool flip;
  int val, xval;
  void push() {
    if (flip) {
      if (c[0]) c[0]->flip ^= 1;
      if (c[1]) c[1]->flip ^= 1;
      swap(c[0], c[1]), flip = 0;
    }
  }
  void pull() {
    xval = val;
    if (c[0]) xval ^= c[0]->xval;
    if (c[1]) xval ^= c[1]->xval;
  }
  bool dir() { return this == p->c[1]; }
  void rot() {
    bool t = dir();
    Node *y = p, *&z = c[!t];
    p = y->p;
    if (p) p->c[y->dir()] = this;
    if (z) z->p = y;
    y->c[t] = z;
    y->p = this;
    (z = y)->pull();
  }
	void g() { if (p) p->g(), pp = p->pp; push(); }
	void splay() {
		for (g(); p; rot()) if (p->p)
      (p->dir() == dir() ? p : this)->rot();
		pull();
	}
	Node *access() {
		for (Node *y = 0, *z = this; z; y = z, z = z->pp) {
			z->splay();
			if (z->c[1]) z->c[1]->pp = z, z->c[1]->p = 0;
			if (y) y->p = z;
			z->c[1] = y;
      z->pull();
		}
		splay();
    flip ^= 1;
		return this;
	} // 2060f82f
};

struct LinkCut {
	vc<Node> nodes;
	LinkCut(int n): nodes(n) {}
	bool cut(int u, int v) {
		Node *y = nodes[v].access();
		Node *x = nodes[u].access();
		if (x->c[0] != y || y->c[1]) return 0;
		x->c[0] = y->p = y->pp = 0;
		x->pull();
		return 1;
	}
	bool is_connected(int u, int v) {
    if (u == v) return 1;
		Node *x = nodes[u].access();
		Node *y = nodes[v].access();
    return x->p;
	}
	bool link(int u, int v) {
		if (is_connected(u, v)) return 0;
		nodes[u].access()->pp = &nodes[v];
		return 1;
	} // 892ea56a
	void update(int u, int c) {
		nodes[u].access()->val = c;
	}
	int query(int u, int v) {
		nodes[v].access();
		return nodes[u].access()->xval;
	}
};
