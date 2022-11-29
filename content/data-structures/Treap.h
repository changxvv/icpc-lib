/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: tested on Luogu
 */
#pragma once

struct Node {
	Node *l = 0, *r = 0;
	int val, y, c = 1;
	Node(int val): val(val), y(rand()) {}
  void pull() {
    c = 1;
    if (l) c += l->c;
    if (r) c += r->c;
  }
};

struct Treap {
  Node *tr = 0;
  int cnt(Node *n) { return n ? n->c : 0; }
  // split is [, )
  pair<Node*, Node*> split(Node* n, int k) { /// start-hash
    if (!n) return {};
    if (cnt(n->l) >= k) { // "n->val >= k" for lower_bound(k)
      auto pa = split(n->l, k);
      n->l = pa.second;
      n->pull();
      return {pa.first, n};
    } else {
      auto pa = split(n->r, k - cnt(n->l)); // or just "k"
      n->r = pa.first;
      n->pull();
      return {n, pa.second};
    }
  } /// end-hash
  Node* merge(Node* l, Node* r) { /// start-hash
    if (!l) return r;
    if (!r) return l;
    if (l->y > r->y) {
      l->r = merge(l->r, r);
      l->pull();
      return l;
    } else {
      r->l = merge(l, r->l);
      r->pull();
      return r;
    }
  } /// end-hash
  Node *ins(Node *t, Node *n, int pos) {
    auto pa = split(t, pos);
    return merge(merge(pa.first, n), pa.second);
  }
  // Example application: move the range [l, r) to index k
  void move(Node *&t, int l, int r, int k) {
    Node *a, *b, *c;
    tie(a,b) = split(t, l); tie(b,c) = split(b, r - l);
    if (k <= l) t = merge(ins(a, b, k), c);
    else t = merge(a, ins(c, b, k - r));
  }
};
