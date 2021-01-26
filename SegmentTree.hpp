
#ifndef TEST_SEGMENT_TREE_H
#define TEST_SEGMENT_TREE_H

#include <cstdio>
#include <cstring>

#include <iostream>
#include <algorithm>

#define rr register
#define lson (u << 1)
#define rson (u << 1 | 1)

typedef long long LL;
const int nMax = 1e5 + 5;
int n, m, q;
int arr[nMax];

inline LL read() {
	LL chtholly = 0, willem = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') willem = -1;
		c = getchar();
	}
	while (c <= '9' && c >= '0') {
		chtholly = chtholly * 10 + (LL)(c - '0');
		c = getchar();
	}
	return chtholly * willem;
}

class SegmentTree {
public:
	LL sum[nMax << 2], addv[nMax << 2], mul[nMax << 2], p;
	inline void pushUp(int u) {
		sum[u] = (sum[lson] + sum[rson]) % p;
	}
	inline void build(int u, int l, int r) {
		addv[u] = 0, mul[u] = 1;
		if (l == r) {
			sum[u] = arr[l];
			return;
		}
		int m = (l + r) >> 1;
		build(lson, l, m);
		build(rson, m + 1, r);
		pushUp(u);
	}
	inline void pushDown(int u, int lc, int rc) {
		if (mul[u] != 1) {
			addv[lson] = (addv[lson] * mul[u]) % p;
			addv[rson] = (addv[rson] * mul[u]) % p;
			mul[lson] = (mul[lson] * mul[u]) % p;
			mul[rson] = (mul[rson] * mul[u]) % p;
			sum[lson] = (sum[lson] * mul[u]) % p;
			sum[rson] = (sum[rson] * mul[u]) % p;
		}
		if (addv[u] != 0) {
			addv[lson] = (addv[lson] + addv[u]) % p;
			addv[rson] = (addv[rson] + addv[u]) % p;
			sum[lson] = (sum[lson] + addv[u] * lc % p) % p;
			sum[rson] = (sum[rson] + addv[u] * rc % p) % p;
		}
		addv[u] = 0, mul[u] = 1;
	}
	inline void updateAdd(int u, int l, int r, int ql, int qr, int val) {
		if (ql <= l && r <= qr) {
			sum[u] = (sum[u] + val * (r - l + 1) % p) % p;
			addv[u] = (addv[u] + val) % p;
			return;
		}
		int m = (l + r) >> 1;
		pushDown(u, m - l + 1, r - m);
		if (ql <= m) updateAdd(lson, l, m, ql, qr, val);
		if (qr > m) updateAdd(rson, m + 1, r, ql, qr, val);
		pushUp(u);
	}
	inline void updateMul(int u, int l, int r, int ql, int qr, int val) {
		if (ql <= l && r <= qr) {
			mul[u] = mul[u] * val % p;
			sum[u] = sum[u] * val % p;
			addv[u] = addv[u] * val % p;
			return;
		}
		int m = (l + r) >> 1;
		pushDown(u, m - l + 1, r - m);
		if (ql <= m) updateMul(lson, l, m, ql, qr, val);
		if (qr > m) updateMul(rson, m + 1, r, ql, qr, val);
		pushUp(u);
	}
	inline LL query(int u, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return sum[u];
		int m = (l + r) >> 1;
		pushDown(u, m - l + 1, r - m);
		LL ret = 0LL;
		if (ql <= m) ret = (ret + query(lson, l, m, ql, qr)) % p;
		if (qr > m) ret = (ret + query(rson, m + 1, r, ql, qr)) % p;
		return ret % p;
	}
};

#endif
