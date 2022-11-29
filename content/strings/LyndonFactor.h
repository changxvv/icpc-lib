/**
 * Author: Benq
 * Description: 
	* A string is "simple" if it is strictly smaller than any of its own nontrivial suffixes.
	* The Lyndon factorization of the string $s$ is a factorization $s=w_1w_2\ldots w_k$
	* where all strings $w_i$ are simple and $w_1\ge w_2\ge \cdots \ge w_k.$ Min rotation
	* gets min index i such that cyclic shift of s starting at i is minimum.
 * Source: https://cp-algorithms.com/string/lyndon_factorization.html
 * Time: O(N)
 */

vs duval(str s) {
	int N = sz(s); vs factors;
	for (int i = 0; i < N; ) {
		int j = i+1, k = i;
		for (; j < N && s[k] <= s[j]; ++j) {
			if (s[k] < s[j]) k = i;
			else ++k;
		}
		for (; i <= k; i += j-k) factors.pb(s.substr(i,j-k));
	}
	return factors;
}
int minRotation(str s) { 
	int N = sz(s); s += s;
	vs d = duval(s); int ind = 0, ans = 0;
	while (ans+sz(d[ind]) < N) ans += sz(d[ind++]);
	while (ind && d[ind] == d[ind-1]) ans -= sz(d[ind--]);
	return ans;
}
