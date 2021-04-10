
#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef unsigned char BYTE;
typedef unsigned int uint;

class Bloom {
public:
	Bloom(int byte, string hashword) : _byte(byte), _bloom(byte, 0), _hashword(hashword) {}
	~Bloom() {}

	void insert(string key) {
		for (auto& c : _hashword)
			_insert(_hash(key, c));
		printf("插入字符串 [%d] %s 成功！\n", __LINE__, key.c_str());
	}
	
	bool search(string key) {
		for (auto& c : _hashword) {
			if (!_search(_hash(key, c))) {
				printf("搜索字符串 [%d] %s 失败！\n", __LINE__, key.c_str());
				return false;
			}
		}
		printf("搜索字符串 [%d] %s 成功！\n", __LINE__, key.c_str());
		return true;
	}

	void showBloom() {
		for (int i = 0; i < _byte; ++i) {
			printf("第[%d]个字节: ");
			for (int j = 0; j < 8; ++j) {
				if (_bloom[i] & (1 << j))
					cout << " 1 ";
				else cout << " 0 ";
			}
			cout << endl;
		}
	}

private:
	uint _byte; // 数组字节数
	vector<BYTE> _bloom;
	string _hashword;

	bool _search(uint idx) {
		auto d = idx / 8;
		auto r = idx % 8;
		return _bloom[d] & (1 << r);
	}

	void _insert(uint idx) {
		auto d = idx / 8;
		auto r = idx % 8;
		_bloom[d] |= (1 << r);
	}

	uint _hash(string& key, char pivot) {
		uint hash = 0;
		for (auto& c : key)
			hash = hash * 11 + (c - pivot);
		return hash % (_byte * 8);
	}
};