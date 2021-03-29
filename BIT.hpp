
#ifndef CPLUSPLUS_TREE_ARRAY_H
#define CPLUSPLUS_TREE_ARRAY_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Binary Indexed Tree
class BIT {
private:
	vector<int> s; // 应该是从下标1开始有意义，s[x]存储[1, x]的区间和
	int n;

	int lowbit(int x) { return x & (-x); }
public:
	BIT(int _n) : s(_n + 1, 0), n(_n) {}

	void update(int x, int v) { // 从下至上更新数组值
		if (x == 0) return;
		while (x <= n) {
			s[x] += v;
			x += lowbit(x);
		}
	}

	int query(int x) { // 返回[1, x]区间上的和
		int ret = 0;
		while (x) {
			ret += s[x];
			x -= lowbit(x);
		}
		return ret;
	}

	int query(int x, int y) { // 返回[x, y]区间上的和
		if (y < x) return 0;
		return query(y) - query(x - 1);
	}
};

class BIT_OR {
private:
	vector<int> s, arr; // 应该是从下标1开始有意义，s[x]存储(x - lowbit(x), x]区间或，arr存储原本的值
	int n;

	int lowbit(int x) { return x & (-x); }
public:
	BIT_OR(int _n) : n(_n), s(_n + 1, 0), arr(_n + 1, 0) {}

	void update(int x, int v) { // 从下到上更新
		s[x] = arr[x] = v;
		while (x <= n) {
			int lx = lowbit(x);
			for (int i = 1; i < lx; i <<= 1) {
				s[x] |= s[x - i];
			}
			x += lx;
		}
	}

	int query(int x) { // 返回[1, x]区间上的和
		int ret = 0;
		while (x) {
			ret |= s[x];
			x -= lowbit(x);
		}
		return ret;
	}

	int query(int x, int y) { // 获取[x, y]区间的或
		int ret = 0;
		while (y >= x) {
			ret |= arr[y], --y; // 秒啊
			while (y - lowbit(y) >= x) { // 如果x不在(y - lowbit[y], y]，可直接使用s[y]
				ret |= s[y];
				y -= lowbit(y);
			}
		}
		return ret;
	}
};

class BIT_MAX {
private:
	vector<int> s, arr; // 应该是从下标1开始有意义，s[x]存储(x - lowbit(x), x]的最大值，arr存储原本的值
	int n;

	int lowbit(int x) { return x & (-x); }
public:
	BIT_MAX(int _n) : n(_n), s(_n + 1, 0), arr(_n + 1, 0) {}

	void update(int x, int v) { // 需要更新包含当前值的区间的最大值 O(lgn*lgn)
		s[x] = arr[x] = v; // 从下到上更新
		while (x <= n) {
			int lx = lowbit(x);
			for (int i = 1; i < lx; i <<= 1) {
				s[x] = max(s[x], s[x - i]);
			}
			x += lx;
		}
	}

	int query(int x) { // 返回[1, x]区间上最大值
		int ret = INT_MIN;
		while (x) {
			ret = max(ret, s[x]);
			x -= lowbit(x);
		}
		return ret;
	}

	int query(int x, int y) { // 返回[x, y]区间上的最大值
		int ret = INT_MIN;
		while (y >= x) {
			ret = max(ret, arr[y]), --y; // 妙得一批
			while (y - lowbit(y) >= x) { // 如果x不在(y - lowbit[y], y]，可直接使用s[y]
				ret = max(ret, s[y]);
				y -= lowbit(y);
			}
		}
		return ret;
	}
};

#endif
