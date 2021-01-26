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

class UnionFind {
public:
	vector<int> parent;
	vector<int> size;
	int n;
	int setCount;

public:
	UnionFind(int _n) : n(_n), setCount(_n), parent(_n), size(_n, 1) {
		iota(parent.begin(), parent.end(), 0);
	}

	int findSet(int x) {
		return parent[x] == x ? x : parent[x] = findSet(parent[x]);
	}

	bool unite(int x, int y) {
		x = findSet(x);
		y = findSet(y);
		if (x == y) {
			return false;
		}
		if (size[x] < size[y]) {
			swap(x, y);
		}
		parent[y] = x;
		size[x] += size[y];
		--setCount;
		return true;
	}

	bool connected(int x, int y) {
		x = findSet(x);
		y = findSet(y);
		return x == y;
	}
};
