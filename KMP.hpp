
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class KMP {
public:
	KMP(string _s, string _t) : s(_s), t(_t), next(_t.size() + 1) {}

	int match() {
		int i = 0, j = 0;
		while (i < int(s.size()) && j < int(t.size())) {
			if (j == -1 || s[i] == t[j])
				i++, j++;
			else j = next[j];
		}
		if (j == t.size()) return i - j;
		return -1;
	}

	void getNext() {
		next[0] = -1;
		int i = 0, j = -1;
		while (i < t.size()) {
			if (j == -1 || t[i] == t[j]) {
				i++;
				j++;
				next[i] = j;
			}
			else j = next[j];
		}
	}

	void showNext() {
		for (auto& x : next)
			cout << x << ' ';
		cout << endl;
	}
private:
	string s, t;
	vector<int> next;
};

class KMP_ {
public:
	KMP_(string _s, string _p) : 
		s(_s), p(_p), next(p.size()) {}
	int match() {
		int i = 0, j = 0;
		while (i < s.size() && j < p.size()) {
			if (s[i] == p[j]) i++, j++;
			else if (j == 0) i++;
			else j = next[j - 1];
		}
		if (j == p.size()) return i - j;
		return -1;
	}
	void getNext() {
		next[0] = 0;
		int i = 1, j = 0;
		while (i < p.size()) {
			if (p[i] == p[j]) {
				next[i] = j + 1;
				i++, j++;
			}
			else if (j == 0) i++;
			else j = next[j - 1];
		}
	}
	void showNext() { for (auto& x : next) cout << x << ' '; cout << endl; }
public:
	string s, p;
	vector<int> next; // next[j] 是以p[j]结尾的部分匹配
};

class __KMP {
public:
	string s, p;
	vector<int> next;

public:
	__KMP(string _s, string _p) : s(_s), p(_p), next(_p.size()) {}
	int match() {
		getNext();
		int i = 0, j = 0;
		while (i < s.size() && j < p.size()) {
			if (s[i] == p[j]) ++i, ++j;
			else if (j == 0) ++i;
			else j = next[j - 1];
		}
		if (j == p.size()) return i - j;
		return -1;
	}
	void getNext() {
		next[0] = 0;
		int i = 1, j = 0;
		while (i < p.size()) {
			if (p[i] == p[j]) {
				next[i] = j + 1;
				++i, ++j;
			}
			else if (j == 0) ++i;
			else j = next[j - 1];
		}
	}
};