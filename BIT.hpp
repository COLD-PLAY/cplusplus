
#ifndef CPLUSPLUS_TREE_ARRAY_H
#define CPLUSPLUS_TREE_ARRAY_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Binary Indexed Tree
class BIT {
private:
	vector<int> s; // Ӧ���Ǵ��±�1��ʼ�����壬s[x]�洢[1, x]�������
	int n;

	int lowbit(int x) { return x & (-x); }
public:
	BIT(int _n) : s(_n + 1, 0), n(_n) {}

	void update(int x, int v) { // �������ϸ�������ֵ
		if (x == 0) return;
		while (x <= n) {
			s[x] += v;
			x += lowbit(x);
		}
	}

	int query(int x) { // ����[1, x]�����ϵĺ�
		int ret = 0;
		while (x) {
			ret += s[x];
			x -= lowbit(x);
		}
		return ret;
	}

	int query(int x, int y) { // ����[x, y]�����ϵĺ�
		if (y < x) return 0;
		return query(y) - query(x - 1);
	}
};

class BIT_OR {
private:
	vector<int> s, arr; // Ӧ���Ǵ��±�1��ʼ�����壬s[x]�洢(x - lowbit(x), x]�����arr�洢ԭ����ֵ
	int n;

	int lowbit(int x) { return x & (-x); }
public:
	BIT_OR(int _n) : n(_n), s(_n + 1, 0), arr(_n + 1, 0) {}

	void update(int x, int v) { // ���µ��ϸ���
		s[x] = arr[x] = v;
		while (x <= n) {
			int lx = lowbit(x);
			for (int i = 1; i < lx; i <<= 1) {
				s[x] |= s[x - i];
			}
			x += lx;
		}
	}

	int query(int x) { // ����[1, x]�����ϵĺ�
		int ret = 0;
		while (x) {
			ret |= s[x];
			x -= lowbit(x);
		}
		return ret;
	}

	int query(int x, int y) { // ��ȡ[x, y]����Ļ�
		int ret = 0;
		while (y >= x) {
			ret |= arr[y], --y; // �밡
			while (y - lowbit(y) >= x) { // ���x����(y - lowbit[y], y]����ֱ��ʹ��s[y]
				ret |= s[y];
				y -= lowbit(y);
			}
		}
		return ret;
	}
};

class BIT_MAX {
private:
	vector<int> s, arr; // Ӧ���Ǵ��±�1��ʼ�����壬s[x]�洢(x - lowbit(x), x]�����ֵ��arr�洢ԭ����ֵ
	int n;

	int lowbit(int x) { return x & (-x); }
public:
	BIT_MAX(int _n) : n(_n), s(_n + 1, 0), arr(_n + 1, 0) {}

	void update(int x, int v) { // ��Ҫ���°�����ǰֵ����������ֵ O(lgn*lgn)
		s[x] = arr[x] = v; // ���µ��ϸ���
		while (x <= n) {
			int lx = lowbit(x);
			for (int i = 1; i < lx; i <<= 1) {
				s[x] = max(s[x], s[x - i]);
			}
			x += lx;
		}
	}

	int query(int x) { // ����[1, x]���������ֵ
		int ret = INT_MIN;
		while (x) {
			ret = max(ret, s[x]);
			x -= lowbit(x);
		}
		return ret;
	}

	int query(int x, int y) { // ����[x, y]�����ϵ����ֵ
		int ret = INT_MIN;
		while (y >= x) {
			ret = max(ret, arr[y]), --y; // ���һ��
			while (y - lowbit(y) >= x) { // ���x����(y - lowbit[y], y]����ֱ��ʹ��s[y]
				ret = max(ret, s[y]);
				y -= lowbit(y);
			}
		}
		return ret;
	}
};

#endif
