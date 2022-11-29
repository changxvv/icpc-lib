/**
 * Author: changxv
 * Date: 2021-05-01
 * License: CC0
 * Source: LOCAL
 * Description: STL BST
 * Time: O(\log N)
 */
#pragma once

#include <ext/rope> /** keep-include */
using namespace __gnu_cxx;
rope<T> rp;
crope rp; // same for rope<char>

/* basic */
size(), operator[]
push_back(key);
insert(pos, x);
erase(pos, x);
replace(pos, x);
substr(pos, x);

/* advanced */
rope<int> *his[N];
his[i] = new rope<int> (*his[i - 1]);
