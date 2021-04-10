
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

typedef unsigned int uint;

class MerkleTree {
public:
	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		uint level; // 当前节点树高
		uint data; // 数据，非叶子节点为hash值
		Node(uint _data, uint _level) : left(nullptr), right(nullptr),
			parent(nullptr), data(_data), level(_level) {}
	};

	MerkleTree(vector<uint>& nums) : _root(nullptr) { _init(nums); }
	
	~MerkleTree() { _deleteMerkleTree(); }

	void insert(uint val) {
		auto node = new Node(val, 0);
		printf("新建叶节点 [%3d] tree_depth=%d, level=%d, data=%-6d\n",
			__LINE__, _root == nullptr ? 0 : _root->level, node->level, node->data);
		if (!_root) { // 如果mt 为空，当前没有树，需要新建一个头节点
			_root = new Node(-1, 1);
			_root->left = node;
			node->parent = _root;
			printf("新建头节点 [%3d] tree_depth=%d, level=%d, data=%-6d\n",
				__LINE__, _root->level, _root->level, _root->data);
			return;
		}
		auto p = _findEmptyNode(_findLastNode(_root));

		if (p) {
			if (p->left->left == nullptr && p->right == nullptr) {
				p->right = node;
				node->parent = p;
				// 更新哈希值
				p->data = _hash(p->left->data, p->right->data);
			}
			else { // 中间节点，需要在右子树上新建和左子树同样深度
				auto l = p->level - 1;
				auto tmp = new Node(-1, l);
				p->right = tmp;
				tmp->parent = p;
				printf("新中间节点 [%3d] tree_depth=%d, level=%d, data=%-6d\n",
					__LINE__, _root->level, tmp->level, tmp->data);

				p = p->right;
				l = p->level - 1; // 更新level - 1

				while (l > 0) {
					tmp = new Node(-1, l);
					p->left = tmp;
					tmp->parent = p;
					printf("新中间节点 [%3d] tree_depth=%d, level=%d, data=%-6d\n",
						__LINE__, _root->level, tmp->level, tmp->data);

					p = p->left;
					--l;
				}
				// 叶子节点赋值
				p->left = node;
				node->parent = p;

				// 自底向上更新哈希值
				while (p != _root) {
					p->data = _hash(p->left->data, p->right == nullptr ? 0 : p->right->data);
					p = p->parent;
				}
				// 更新根节点哈希值
				p->data = _hash(p->left->data, p->right == nullptr ? 0 : p->right->data);
			}
		}
		else { // 已经是满二叉树了，需要增加头节点，level也要加1
			auto tmp = _root;

			_root = new Node(-1, tmp->level + 1);
			_root->left = tmp;
			tmp->parent = _root;
			printf("新建头节点 [%3d] tree_depth=%d, level=%d, data=%-6d\n",
				__LINE__, _root->level, _root->level, _root->data);

			// 创建头节点的第一个right子节点
			tmp = new Node(-1, _root->level - 1);
			_root->right = tmp;
			tmp->parent = _root;
			printf("新中间节点 [%3d] tree_depth=%d, level=%d, data=%-6d\n",
				__LINE__, _root->level, tmp->level, tmp->data);

			// 从这里开始创建新的子树
			p = _root->right;
			auto l = p->level - 1;

			// 根据树的深度创建同样深的左子树
			while (l > 0) {
				tmp = new Node(-1, l);
				p->left = tmp;
				tmp->parent = p;
				printf("新中间节点 [%3d] tree_depth=%d, level=%d, data=%-6d\n",
					__LINE__, _root->level, tmp->level, tmp->data);

				p = p->left;
				--l;
			}
			// 叶子节点赋值
			p->left = node;
			node->parent = p;

			// 自底向上更新哈希值
			while (p != _root) {
				p->data = _hash(p->left->data, p->right == nullptr ? 0 : p->right->data);
				p = p->parent;
			}
			// 更新根节点哈希值
			p->data = _hash(p->left->data, p->right == nullptr ? 0 : p->right->data);
		}
	}

	void printMerkleTree() { cout << endl; _inOrder(_root, 0); cout << endl; }

private:
	Node* _root;

	void _deleteMerkleTree() { _deleteMerkleTree(_root); }

	void _init(vector<uint>& nums) {
		for (auto& x : nums)
			insert(x);
		printf("Merkle Tree 创建完毕！！！\n");
	}

	void _deleteMerkleTree(Node* p) {
		if (!p) return;
		if (!p->left && !p->right) {
			printf("回收叶子节点 [%3d] level=%d, data=%d\n", __LINE__, p->level, p->data);
			delete p;
			return;
		}
		_deleteMerkleTree(p->left);
		_deleteMerkleTree(p->right);
		printf("回收中间节点 [%3d] level=%d, data=%d\n", __LINE__, p->level, p->data);
		delete p;
	}

	void _inOrder(Node* p, int depth) {
		if (!p) return;
		_inOrder(p->left, depth + 1);
		for (int i = 0; i < depth; ++i)
			printf("           ");
		printf("------>%-6d\n", p->data);
		_inOrder(p->right, depth + 1);
	}

	Node* _findLastNode(Node* mt) {
		if (!mt->left && !mt->right) // 叶子节点
			return mt;
		if (mt->right) // 存在右儿子
			return _findLastNode(mt->right);
		return _findLastNode(mt->left); // 只有左儿子
	}

	Node* _findEmptyNode(Node* mt) {
		auto p = mt->parent;
		while (p->parent && p->left && p->right)
			p = p->parent;
		if (!p->parent && p->left && p->right) // 到顶了
			return nullptr;
		return p;
	}

	uint _hash(string key) {
		uint cal = 11, hash = 0;
		for (auto& c : key) {
			hash += hash * cal + c;
		}
		return hash & 0x7fffffff;
	}

	uint _hash(int x) {
		uint cal = 11, hash = 0;
		hash = x * cal;
		return hash & 0x7fffffff;
	}

	uint _hash(uint x, uint y) {
		uint cal = 11, hash = 0;
		hash = (x + y) * cal;
		return hash & 0x7fffffff;
	}
};