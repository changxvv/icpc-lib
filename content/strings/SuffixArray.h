/**
 * Author: 罗穗骞, chilli
 * Date: 2019-04-11
 * License: Unknown
 * Source: Suffix array - a powerful tool for dealing with strings
 * (Chinese IOI National team training paper, 2009)
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{ht} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{ht[i] = ht(sa[i], sa[i-1])}, \texttt{ht[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

struct SA {
  vc<int> sa, ht, rk;
  SA(string s, int lim = 256) {
    int n = sz(s) + 1, k = 0, a, b, i, j, p;
    vc<int> x(all(s) + 1), y(n), ws(max(n, lim));
    rk = sa = ht = y, iota(all(sa), 0);
    for (j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
      p = j, iota(all(y), n - j);
      for (i = 0; i < n; ++i) if (sa[i] >= j) y[p++] = sa[i]-j;
      fill(all(ws), 0);
      for (i = 0; i < n; ++i) ++ws[x[i]];
      for (i = 1; i < lim; ++i) ws[i] += ws[i - 1];
      for (i = n; i--; ) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      for (i = 1; i < n; ++i) {
        a = sa[i - 1], b = sa[i];
        x[b] = (y[a]==y[b] && y[a+j]==y[b+j]) ? p - 1 : p++;
      }
    }
    for (i = 1; i < n; ++i) rk[sa[i]] = i;
    for (i = 0; i < n - 1; ht[rk[i++]] = k)
      for (k && --k, j = sa[rk[i] - 1]; s[i+k] == s[j+k]; ++k);
  }
};
