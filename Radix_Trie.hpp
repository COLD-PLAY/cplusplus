
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <queue>

using namespace std;

// �ص�������
typedef function<void(string, int)> Callback;

// ʵ��һ���򵥵�Trie ǰ׺��
class Trie {
public:
	Trie() : root(new Node(0)) {}
	~Trie() { delete root; } // ��������

	void insert(string key, int val) {
		auto cur = root;
		for (auto& c : key) { // �ͱ����Ҿ����ˣ��������
			if (!cur->kids.count(c)) // �Ҳ������½�
				cur->kids[c] = new Node(0);
			cur = cur->kids[c];
		}
		cur->val = val; // ��val
	}

	int search(string key) {
		auto cur = root;
		for (auto& c : key) { // �����ң��Ҳ�������0��ֻ�����0����
			if (!cur->kids.count(c))
				return 0;
			cur = cur->kids[c];
		}
		return cur->val;
	}

	bool startsWith(string prefix) {
		auto cur = root;
		for (auto& c : prefix) { // ������
			if (!cur->kids.count(c))
				return false;
			cur = cur->kids[c];
		}
		return true;
	}

	void foreach(Callback cb) { // ���������cb���ڴ���key��val��test����ֱ�Ӿ�cout�ˣ�
		queue<pair<Node*, string>> que;
		que.push({root, ""}); // ��̫��д�ݹ飬��ֱ�Ӷ�����
		string str;
		while (que.size()) {
			auto cur = que.front();
			if (cur.first->val != 0)
				cb(cur.second, cur.first->val);
			que.pop();
			for (auto it = cur.first->kids.begin(); it != cur.first->kids.end(); ++it)
				que.push({it->second, cur.second + it->first});
		}
	}
private:
	struct Node {
		int val;
		unordered_map<char, Node*> kids;
		
		Node(int _val) : val(_val) {}
		~Node() { // ��������
			for (auto it = kids.begin(); it != kids.end(); ++it)
				delete it->second;
		}
	};
	Node* root;
};

// ʵ��һ���򵥵�radix tree
class RadixTree {
public:
	RadixTree() : root(new Node("", 0)) {}
	~RadixTree() { delete root; }

	void insert(string key, int val) {
		root->insert(key, val);
	}
	int search(string key) {
		return root->search(key);
	}
	void foreach(Callback cb) {
		root->foreach(cb);
	}
private:
	struct Node {
		string _prefix;
		int _val;
		unordered_map<char, Node*> _kids; // �ӽڵ�

		Node(string prefix, int val) : _prefix(prefix), _val(val) {}
		void split(int n) { // �ֲ����
			auto child = new Node(_prefix.substr(n + 1), _val);
			child->_kids = _kids;
			_kids.clear();
			_kids[_prefix.at(n)] = child;
			_prefix = _prefix.substr(0, n);
			_val = 0;
		}
		int commonPrefix(string s, string t) { // ����ǰ׺����
			int c = 0, n1 = s.size(), n2 = t.size();
			while (c < n1 && c < n2) {
				if (s[c] != t[c]) break;
				++c;
			}
			return c;
		}
		Node* findOrCreateKid(char ch) { // ���ӽڵ�����½�һ��
			if (!_kids.count(ch))
				_kids[ch] = new Node("", 0); // �½�һ���յģ������ʱ����
			return _kids[ch];
		}
		void insert(string key, int val) {
			// 1. ֱ�ӿ��Բ���ýڵ�
			if (_prefix == "" && _val == 0 && _kids.empty()) {
				_prefix = key, _val = val;
				return;
			}
			if (_prefix == key) { // 2. ֱ�Ӿ��ǵ�ǰ�ڵ㣬ֻ��Ҫ��_val���и��ļ���
				_val = val;
				return;
			}

			// ��ȡ��ǰ��ǰ׺����Ҫ�ڴ˻�������Ҫ�����key�Ĺ���ǰ׺
			int n = commonPrefix(_prefix, key);
			if (_prefix.size() > n) // �����ǰǰ׺���ȱȹ���ǰ׺��������Ҫ�ֲ�
				split(n); // �ֲ���ʵ���ǰѵ�ǰ�ڵ���Ϊ���սڵ㲢��Ŀǰ��Ĺ���ǰ׺��_prefix.substr(0, n)��Ϊ��ǰǰ׺��
			if (key.size() > n) { // 3. ���ǵ�ǰ��Ҫ�����key�������ǰ׺��������Ҫ�ڷֲ���ӽڵ��ϲ��룩
				auto kid = findOrCreateKid(key.at(n));
				kid->insert(key.substr(n + 1), val); // ���ϣ����һ�����ֲ�ʱֻ�ǽ�����ǰ׺���1���ַ���Ϊmap��key�����������Ϊ�ӽڵ��_prefix��
			}
			else { // key == commonPrefixʱ����ʱֻ��Ҫ��_prefix���зֲ棬��ǰ��ֱ����Ϊһ��key:val
				_val = val;
			}
		}
		int search(string key) {
			if (key == _prefix) // ���յĵݹ��˳��������ҵ���
				return _val;
			int n = commonPrefix(_prefix, key);
			if (n == _prefix.size() && _kids.count(key.at(n))) // ����������Ҳ�����
				return _kids[key.at(n)]->search(key.substr(n + 1)); // �
			return 0;
		}
		void foreach(Callback cb) { // ������ӡ��������������ȡ����cb����
			if (_val > 0)
				cb(_prefix, _val);

			for (auto it = _kids.begin(); it != _kids.end(); ++it) {
				it->second->foreach([&](string key, int val) { // Golang����������������������
					cb(_prefix + it->first + key, val); // ���һ��
				});
			}
		}
	};
	Node* root;
};