/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: p[x] computes the length of the longest prefix of s that ends at x, other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 * Status: Tested on Luogu KMP
 */
#pragma once

auto getBorder = [](string s) {
	vc<int> p(sz(s));
	for (int i = 1; i < sz(s); ++i) {
		int g = p[i - 1];
		while (g && s[g] != s[i]) g = p[g - 1];
		p[i] = g + (s[g] == s[i]);
	}
	return p;
}; // 43f874fa

auto KMP = [&getBorder](string s, string pat) {
	vc<int> p = getBorder(pat + '\0' + s), ans;
	for (int i = sz(p) - sz(s); i < sz(p); ++i) {
		if (p[i] == sz(pat)) ans.emplace_back(i - 2 * sz(pat));
	}
	return ans;
}; // 8ffe484c
