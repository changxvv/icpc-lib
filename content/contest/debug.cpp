template<class U, class T>
enable_if_t<is_same_v<U, ostream>, U&>
operator << (U &os, T v) {
	os << "{ ";
	for (auto e: v) os << e << ' ';
	return os << '}';
}
ostream &operator << (ostream &os, pair<int, int> p) {
	return os << '(' << p.first << ", " << p.second << ')';
}
void dbg() { cerr << "\n"; }
template<class T, class ...U>
void dbg(T e, U ...a) { cerr << e << ' '; dbg(a...); }
#define err(A...) cerr << #A ": ", dbg(A)

