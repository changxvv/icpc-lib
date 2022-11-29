/**
 * Author: changxv
 * Date: 2021-08-14
 * License: CC0
 * Source: myself
 * Description: Calculate some arithmetic function in linear time.
 * Time: O(n)
 * Status: Untested
 */
#pragma once

constexpr int LIM = 1e6 + 1; // change this
vc<int> pr, d(LIM), w(d), mu(d), phi(d); 
bitset<LIM> n_pr;
auto eulerSieve = [&] {
  pr.reserve(int(LIM / log(LIM) * 1.1));
  phi[1] = d[1] = w[1] = mu[1] = n_pr[1] = 1;
  for (int i = 2; i < LIM; ++i) {
    if (!n_pr[i]) {
      pr.emplace_back(i);
      phi[i] = i - 1, mu[i] = -1, d[i] = 2, w[i] = i + 1;
    }
    for (auto p: pr) {
      int t = p * i;
      if (t >= LIM) break;
      n_pr[t] = 1;
      if (i % p == 0) {
        phi[t] = phi[i] * p, mu[t] = 0;
        d[t] = d[i] * 2 - d[i / p];
        w[t] = w[i] + p * (w[i] - w[i / p]);
      } else {
        phi[t] = phi[i] * (p - 1), mu[t] = -mu[i];
        d[t] = d[i] * 2;
        w[t] = w[i] * (p + 1);
      }
    }
  }
};
