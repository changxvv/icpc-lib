/**
 * Author: Per Austrin, Ulf Lundstrom
 * Date: 2009-04-09
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 Apply the linear transformation (translation, rotation and scaling) which takes line p0-p1 to line q0-q1 to point r. P should be double.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-8mm}
\includegraphics[width=\textwidth]{content/geometry/linearTransformation}
\vspace{-2mm}
\end{minipage}
 * Status: not tested
 */
#pragma once

#include "Point.h"

template<class P>
P linearTransformation(P p0, P p1, P q0, P q1, P r) {
	P dp = p1 - p0, num(dp.cross(q1 - q0), dp.dot(q1 - q0));
	return q0 + P((r-p0).cross(num), (r-p0).dot(num))/dp.dist2();
}
