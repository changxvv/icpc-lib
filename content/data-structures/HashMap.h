/**
 * Author: Simon Lindholm, chilli
 * Date: 2018-07-23
 * License: CC0
 * Source: http://codeforces.com/blog/entry/60737
 * Description: Hash map with mostly the same API as unordered\_map, but \tilde
 * 3x faster. Uses 1.5x memory.
 * Initial capacity must be a power of 2 (if provided).
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp> /** keep-include */
#include <ext/pb_ds/hash_policy.hpp> /** keep-include */
struct chash {
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
	ll operator()(ll x) const { 
    return __builtin_bswap64((x^RANDOM)*C); 
  }
};
template<class K, class V> using ht = __gnu_pbds::gp_hash_table<K,V,chash>;
template<class K, class V> V get(ht<K, V> &u, K x) {
	auto it = u.find(x);
	return it == end(u) ? 0 : it->s;
}

