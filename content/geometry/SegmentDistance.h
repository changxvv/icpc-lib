/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
Returns the shortest distance between point p and the line segment from point s to e. P should be double.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"


template<class P> double segDist(P s, P e, P p) {
	if (s == e) return (p - s).dist();
	auto d = (e - s).dist2(), t = clamp((p - s).dot(e - s),0.,d);
	return ((p - s) * d - (e - s) * t).dist() / d;
}
