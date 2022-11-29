#pragma once

template<class F>
struct YCombinator {
  F f;
  template<class T> YCombinator(T &&f): f(forward<T>(f)) {}
  template<class ...U> auto operator()(U &&...a) { 
    return f(ref(*this), forward<U>(a)...); 
  }
};
template<class F> auto YF(F &&f) { 
  return YCombinator<decay_t<F>>(forward<F>(f)); 
}
