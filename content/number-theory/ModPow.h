/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description:
 * Time: O(\log n)
 * Status: tested
 */
#pragma once

#include "ModularArithmetic.h"

constexpr ll md = 1000000007; // change this
auto mdPow = [&](Mod b, ll e) {
  Mod res = 1;
  for (; e; b *= b, e /= 2)
    if (e & 1) res *= b;
  return res;
};
