
#include <iostream>
#include <vector>

using namespace std;

class Skiplist {
private:
	static constexpr int MAXL = 32;
	static constexpr int P = 4;
	static constexpr int S = 0xffff;
	static constexpr int PS = S / 4;
	struct Node {
		int val;
		vector<Node*> level;
		Node(int _val, int _sz = 32)
			: val(_val), level(_sz, nullptr) {}
	};
	Node* head, * tail;
	int level, length;

public:
	Skiplist() {
		level = length = 0;
		tail = new Node(-1, 0);
		head = new Node(-1);
		for (int i = 0; i < MAXL; ++i) {
			head->level[i] = tail;
		}
	}

	Node* find(int val) {
		auto p = head;
		for (int i = level - 1; i >= 0; --i) {
			while (p->level[i] && p->level[i]->val < val)
				p = p->level[i];
		}
		p = p->level[0];
		return p;
	}

	bool search(int target) {
		auto p = find(target);
		return p->val == target;
	}

	void add(int val) {
		vector<Node*> update(MAXL);
		auto p = head;
		for (int i = level - 1; i >= 0; --i) {
			while (p->level[i] && p->level[i]->val < val)
				p = p->level[i];
			update[i] = p;
		}
		int lv = randomLevel();
		if (lv > level) {
			lv = ++level;
			update[lv - 1] = head;
		}
		auto node = new Node(val, lv);
		for (int i = lv - 1; i >= 0; --i) {
			p = update[i];
			node->level[i] = p->level[i];
			p->level[i] = node;
		}
		++length;
	}

	bool erase(int val) {
		vector<Node*> update(MAXL + 1);
		auto p = head;
		for (int i = level - 1; i >= 0; --i) {
			while (p->level[i] && p->level[i]->val < val)
				p = p->level[i];
			update[i] = p;
		}
		p = p->level[0];
		if (p->val != val)
			return false;
		for (int i = 0; i < level; ++i) {
			if (update[i]->level[i] != p)
				break;
			update[i]->level[i] = p->level[i];
		}
		while (level > 0 && head->level[level - 1] == tail)
			--level;
		--length;
		return true;
	}

	int randomLevel() {
		int lv = 1;
		while (lv < MAXL && (rand() & S) < PS)
			++lv;
		return lv;
	}
};