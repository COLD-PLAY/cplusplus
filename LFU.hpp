
#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

class LFUCache {
private:
	struct Node {
		int cnt;
		int time;
		int key, value;

		Node(int _cnt, int _time, int _key, int _value)
			: cnt(_cnt), time(_time), key(_key), value(_value) {}

		bool operator<(const Node& rhs) const {
			return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
		}
	};
	int capacity, time;
	unordered_map<int, Node> key_table;
	set<Node> S;

public:
	LFUCache(int _capacity) : capacity(_capacity), time(0) {
		key_table.clear();
		S.clear();
	}
	
	int get(int key) {
		if (capacity == 0) return -1;
		auto it = key_table.find(key);
		if (it == key_table.end()) return -1;
		Node cache = it->second;
		S.erase(cache);
		cache.cnt += 1;
		cache.time = ++time;
		S.insert(cache);
		it->second = cache;
		return cache.value;
	}

	void put(int key, int value) {
		if (capacity == 0) return;
		auto it = key_table.find(key);
		if (it == key_table.end()) {
			if (key_table.size() == capacity) {
				key_table.erase(S.begin()->key);
				S.erase(S.begin());
			}
			Node cache = Node(1, ++time, key, value);
			key_table.insert({key, cache});
			S.insert(cache);
		}
		else {
			Node cache = it->second;
			S.erase(cache);
			cache.cnt += 1;
			cache.time = ++time;
			cache.value = value;
			S.insert(cache);
			it->second = cache;
		}
	}
};

class LFUCache_ {
private:
	struct Node {
		int cnt, time;
		int key, val;

		Node(int _cnt, int _time, int _key, int _val)
			: cnt(_cnt), time(_time), key(_key), val(_val) {}

		bool operator<(const Node& rhs) const {
			return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
		}
	};

	unordered_map<int, Node> cache;
	set<Node> lfu;
	int size;
	int cap;
	int time;
	
public:
	LFUCache_(int _cap) : cap(_cap), time(0), size(0) {
		cache.clear();
		lfu.clear();
	}

	int get(int key) {
		if (cap == 0) return -1;
		auto it = cache.find(key);
		if (it == cache.end()) return -1;
		auto node = it->second;
		lfu.erase(node);
		node.cnt += 1;
		node.time = ++time;
		lfu.insert(node);
		it->second = node;
		return node.val;
	}

	void put(int key, int val) {
		if (cap == 0) return;
		auto it = cache.find(key);
		if (it == cache.end()) {
			if (size == cap) {
				auto removed = lfu.begin();
				cache.erase(removed->key);
				lfu.erase(removed);
				--size;
			}
			auto node = Node(1, ++time, key, val);
			cache.insert({ key, node });
			lfu.insert(node);
			++size;
		}
		else {
			auto node = it->second;
			lfu.erase(node);
			node.cnt += 1;
			node.time = ++time;
			node.val = val;
			lfu.insert(node);
			it->second = node;
		}
	}
};

class LFUCache__ {
private:
	struct Node {
		int key, val, freq;
		Node(int _key, int _val, int _freq)
			: key(_key), val(_val), freq(_freq) {}
	};

	int minfreq, capacity;
	unordered_map<int, list<Node>::iterator> key_table;
	unordered_map<int, list<Node>> freq_table;

public:
	LFUCache__(int _capacity) : capacity(_capacity), minfreq(0) {
		key_table.clear();
		freq_table.clear();
	}

	int get(int key) {
		if (capacity == 0) return -1;
		auto it = key_table.find(key);
		if (it == key_table.end()) return -1;
		auto node = it->second;
		int val = node->val, freq = node->freq;
		freq_table[freq].erase(node);
		if (freq_table[freq].size() == 0) {
			freq_table.erase(freq);
			if (minfreq == freq) minfreq += 1;
		}
		freq_table[freq + 1].push_front(Node(key, val, freq + 1));
		key_table[key] = freq_table[freq + 1].begin();
		return val;
	}

	void put(int key, int value) {
		if (capacity == 0) return;
		auto it = key_table.find(key);
		if (it == key_table.end()) {
			if (key_table.size() == capacity) {
				auto it2 = freq_table[minfreq].back();
				key_table.erase(it2.key);
				freq_table[minfreq].pop_back();
				if (freq_table[minfreq].size() == 0) {
					freq_table.erase(minfreq);
				}
			}
			freq_table[1].push_front(Node(key, value, 1));
			key_table[key] = freq_table[1].begin();
			minfreq = 1;
		}
		else {
			auto node = it->second;
			int freq = node->freq;
			freq_table[freq].erase(node);
			if (freq_table[freq].size() == 0) {
				freq_table.erase(freq);
				if (minfreq == freq) minfreq += 1;
			}
			freq_table[freq + 1].push_front(Node(key, value, freq + 1));
			key_table[key] = freq_table[freq + 1].begin();
		}
	}
};