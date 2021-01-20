
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