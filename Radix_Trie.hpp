
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <queue>

using namespace std;

// 回调处理函数
typedef function<void(string, int)> Callback;

// 实现一个简单的Trie 前缀树
class Trie {
public:
	Trie() : root(new Node(0)) {}
	~Trie() { delete root; } // 析构函数

	void insert(string key, int val) {
		auto cur = root;
		for (auto& c : key) { // 就遍历找就行了，容易理解
			if (!cur->kids.count(c)) // 找不到就新建
				cur->kids[c] = new Node(0);
			cur = cur->kids[c];
		}
		cur->val = val; // 存val
	}

	int search(string key) {
		auto cur = root;
		for (auto& c : key) { // 遍历找，找不到返回0，只存大于0的数
			if (!cur->kids.count(c))
				return 0;
			cur = cur->kids[c];
		}
		return cur->val;
	}

	bool startsWith(string prefix) {
		auto cur = root;
		for (auto& c : prefix) { // 遍历找
			if (!cur->kids.count(c))
				return false;
			cur = cur->kids[c];
		}
		return true;
	}

	void foreach(Callback cb) { // 遍历输出，cb用于处理key，val（test代码直接就cout了）
		queue<pair<Node*, string>> que;
		que.push({root, ""}); // 不太好写递归，就直接队列了
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
		~Node() { // 析构函数
			for (auto it = kids.begin(); it != kids.end(); ++it)
				delete it->second;
		}
	};
	Node* root;
};

// 实现一个简单的radix tree
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
		unordered_map<char, Node*> _kids; // 子节点

		Node(string prefix, int val) : _prefix(prefix), _val(val) {}
		void split(int n) { // 分叉操作
			auto child = new Node(_prefix.substr(n + 1), _val);
			child->_kids = _kids;
			_kids.clear();
			_kids[_prefix.at(n)] = child;
			_prefix = _prefix.substr(0, n);
			_val = 0;
		}
		int commonPrefix(string s, string t) { // 公共前缀长度
			int c = 0, n1 = s.size(), n2 = t.size();
			while (c < n1 && c < n2) {
				if (s[c] != t[c]) break;
				++c;
			}
			return c;
		}
		Node* findOrCreateKid(char ch) { // 找子节点或者新建一个
			if (!_kids.count(ch))
				_kids[ch] = new Node("", 0); // 新建一个空的（插入的时候用
			return _kids[ch];
		}
		void insert(string key, int val) {
			// 1. 直接可以插入该节点
			if (_prefix == "" && _val == 0 && _kids.empty()) {
				_prefix = key, _val = val;
				return;
			}
			if (_prefix == key) { // 2. 直接就是当前节点，只需要对_val进行更改即可
				_val = val;
				return;
			}

			// 获取当前的前缀和需要在此基础上需要插入的key的公共前缀
			int n = commonPrefix(_prefix, key);
			if (_prefix.size() > n) // 如果当前前缀长度比公共前缀更长，需要分叉
				split(n); // 分叉其实就是把当前节点置为非终节点并将目前最长的公共前缀（_prefix.substr(0, n)作为当前前缀）
			if (key.size() > n) { // 3. 若是当前需要插入的key比最长公共前缀更长（需要在分叉的子节点上插入）
				auto kid = findOrCreateKid(key.at(n));
				kid->insert(key.substr(n + 1), val); // 如上，妙得一批（分叉时只是将公共前缀后的1个字符作为map的key，后面的则作为子节点的_prefix）
			}
			else { // key == commonPrefix时，此时只需要对_prefix进行分叉，当前就直接作为一个key:val
				_val = val;
			}
		}
		int search(string key) {
			if (key == _prefix) // 最终的递归退出条件（找到了
				return _val;
			int n = commonPrefix(_prefix, key);
			if (n == _prefix.size() && _kids.count(key.at(n))) // 不满足就是找不到了
				return _kids[key.at(n)]->search(key.substr(n + 1)); // 妙啊
			return 0;
		}
		void foreach(Callback cb) { // 遍历打印或者其他操作，取决于cb函数
			if (_val > 0)
				cb(_prefix, _val);

			for (auto it = _kids.begin(); it != _kids.end(); ++it) {
				it->second->foreach([&](string key, int val) { // Golang的匿名函数看起来更方便
					cb(_prefix + it->first + key, val); // 妙得一批
				});
			}
		}
	};
	Node* root;
};