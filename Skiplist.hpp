
#include <iostream>
#include <vector>

using namespace std;

static const int SKIPLIST_P_VAL = RAND_MAX / 4;
static const int MAX_LEVEL = 32;

class Skiplist {
public:
	struct Node {
		int val;
		vector<Node*> level;
		Node(int val, int size=MAX_LEVEL)
			: val(val), level(size) {}
	};

	Node* head;
	int maxlevel = 1;
	Skiplist() : head(new Node(INT_MIN, MAX_LEVEL)) {}
	//~Skiplist() { /*delete all nodes*/ }
	
	bool search(int target) {
		auto prev = _search(target)[0];
		return prev->level[0] && prev->level[0]->val == target;
	}
	
	vector<Node*> _search(int key) {
		auto cur = head;
		vector<Node*> prevs(MAX_LEVEL);
		for (int i = maxlevel - 1; i >= 0; --i) {
			while (cur->level[i] && cur->level[i]->val < key)
				cur = cur->level[i];
			prevs[i] = cur;
		}

		return prevs;
	}

	void add(int val) {
		auto prevs = _search(val);
		int level = random_level();
		if (level > maxlevel) {
			for (int i = maxlevel; i < level; ++i)
				prevs[i] = head;
			maxlevel = level;
		}
		auto cur = new Node(val, level);
		for (int i = level - 1; i >= 0; --i) {
			cur->level[i] = prevs[i]->level[i];
			prevs[i]->level[i] = cur;
		}
	}

	bool erase(int val) {
		auto prevs = _search(val);
		if (!prevs[0]->level[0] || prevs[0]->level[0]->val != val)
			return false;
		auto del = prevs[0]->level[0];
		for (int i = 0; i < maxlevel; ++i)
			if (prevs[i]->level[i] == del)
				prevs[i]->level[i] = del->level[i];
		delete del;
		while (maxlevel > 1 && !head->level[maxlevel - 1])
			--maxlevel;
		return true;
	}

	static int random_level() {
		int level = 1;
		while (rand() < SKIPLIST_P_VAL && level < MAX_LEVEL)
			++level;
		return level;
	}
};

class Skiplist_ {
public:
	static const int ML = 32;
	static const int P = RAND_MAX / 4;
	struct Node {
		int val;
		vector<Node*> level;
		Node(int val, int l)
			: val(val), level(l) {}
	};
	int curLevel = 1;
	Node* head;
	
	Skiplist_(int l = ML) {
		head = new Node(-1, l);
	}

	static int randomLevel() {
		int level = 1;
		while (rand() < P && level < ML)
			++level;
		return level;
	}

	vector<Node*> _search(int target) {
		vector<Node*> prevs(ML);
		auto cur = head;
		for (int i = curLevel - 1; i >= 0; --i) {
			while (cur->level[i] && cur->level[i]->val < target)
				cur = cur->level[i];
			prevs[i] = cur;
		}
		return prevs;
	}

	bool search(int target) {
		auto prev = _search(target)[0];
		return prev->level[0] && prev->level[0]->val == target;
	}

	void add(int num) {
		int level = randomLevel();
		auto prevs = _search(num);
		if (level > curLevel) {
			for (int i = curLevel; i < level; ++i)
				prevs[i] = head;
			curLevel = level;
		}
		auto cur = new Node(num, level);
		for (int i = level - 1; i >= 0; --i) {
			cur->level[i] = prevs[i]->level[i];
			prevs[i]->level[i] = cur;
		}
	}

	bool erase(int num) {
		auto prevs = _search(num);
		if (!prevs[0]->level[0] || prevs[0]->level[0]->val != num)
			return false;

		auto del = prevs[0]->level[0];
		for (int i = 0; i < curLevel; ++i) {
			if (prevs[i]->level[i] == del)
				prevs[i]->level[i] = del->level[i];
		}
		delete del;
		if (curLevel > 1 && !head->level[curLevel - 1])
			--curLevel;
		return true;
	}
};