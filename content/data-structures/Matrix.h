/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int, 3> A;
 *  A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
 *  vector<int> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
#pragma once

template<class T, int N>
struct Matrix {
  using M = Matrix;
	array<array<T, N>, N> d{};
	M operator * (const M &m) const {
		M a;
    for (int i = 0; i < N; ++i) 
      for (int k = 0; k < N; ++k) 
        for (int j = 0; j < N; ++j) 
          a.d[i][j] += d[i][k] * m.d[k][j];
		return a;
	}
	vc<T> operator * (const vc<T> &vec) const {
		vc<T> ret(N);
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        ret[i] += d[i][j] * vec[j];
		return ret;
	}
	M operator ^ (int p) const {
		assert(p >= 0);
		M a, b(*this);
    for (int i = 0; i < N; ++i) a.d[i][i] = 1;
		while (p) {
			if (p&1) a = a * b;
			b = b * b;
			p /= 2;
		}
		return a;
	}
};
