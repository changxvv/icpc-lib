/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Time: O(\log N)
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp> /** keep-include */
#include <ext/pb_ds/tree_policy.hpp> /** keep-include */
using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

/* basic */
begin(), end(), size(), empty(), clear()
insert(pair<key, T>), erase(iter), erase(key), operator[]
find(key), lower_bound(key), upper_bound(key)

/* advanced */
order_of_key(key); // number of element less than key

// return the iter of order+1, end() if too large
find_by_order(size_type order); 

// join the other if their ranges don't intersect
join(tree &other);

// split tr and overide other with element larger than key
tr.split(key, tree &other); 
