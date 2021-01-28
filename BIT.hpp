
#ifndef CPLUSPLUS_TREE_ARRAY_H
#define CPLUSPLUS_TREE_ARRAY_H

#include <iostream>
#include <vector>

using namespace std;

// Binary Indexed Tree
class BIT {
private:
	vector<int> s;
	int n;
public:
	BIT(int _n) : s(_n, 0), n(_n) {}

	int lowbit(int a) { return a & (-a); }

	void update(int a, int value) {
		if (a == 0) return;
		while (a <= n) {
			s[a] += value;
			a += lowbit(a);
		}
	}

	int query(int a) {
		int ans = 0;
		while (a) {
			ans += s[a];
			a -= lowbit(a);
		}
	}

	int query(int a, int b) {
		if (b < a) return 0;
		return query(b) - query(a);
	}
};

#endif
