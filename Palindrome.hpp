
#ifndef CPLUSPLUS_PALINDROME_H
#define CPLUSPLUS_PALINDROME_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Palindrome {
public:
	int n;
	vector<vector<bool>> p;

public:
	Palindrome(string s) : n(s.length()), p(n, vector<bool>(n)) {
		for (int i = n - 1; i >= 0; --i) {
			p[i][i] = true;
			for (int j = i + 1; j < n; ++j) if (s[i] == s[j]) {
				p[i][j] = (j == i + 1) || (p[i + 1][j - 1]);
			}
		}
	}

	bool isPalindrome() {
		return p[0][n - 1];
	}
	
	bool isPalindrome(int i, int j) {
		return p[i][j];
	}
};

#endif
