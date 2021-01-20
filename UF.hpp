#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class UF {
public:
	UF(int n) : cnt(n), sz(n, 1) {
		iota(fa.begin(), fa.end(), 1);
	}
	bool connected(int p, int q) {
		return root(p) == root(q);
	}
	int root(int p) {
		while (p != fa[p]) p = fa[fa[p]];
		return p;
	}
	bool connect(int p, int q) {
		int rp = root(p);
		int rq = root(q);
		if (rp == rq) return false;
		if (sz[rp] > sz[rq]) swap(rp, rq);
		fa[rp] = rq;
		sz[rq] += sz[rp];
		cnt -= 1;
		return true;
	}

private:
	vector<int> fa;
	vector<int> sz;
	int cnt;
};
