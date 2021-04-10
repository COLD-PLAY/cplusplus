
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
		uint level; // ��ǰ�ڵ�����
		uint data; // ���ݣ���Ҷ�ӽڵ�Ϊhashֵ
		Node(uint _data, uint _level) : left(nullptr), right(nullptr),
			parent(nullptr), data(_data), level(_level) {}
	};

	MerkleTree(vector<uint>& nums) : _root(nullptr) { _init(nums); }
	
	~MerkleTree() { _deleteMerkleTree(); }

	void insert(uint val) {
		auto node = new Node(val, 0);
		printf("�½�Ҷ�ڵ� [%3d] tree_depth=%d, level=%d, data=%-6d\n",
			__LINE__, _root == nullptr ? 0 : _root->level, node->level, node->data);
		if (!_root) { // ���mt Ϊ�գ���ǰû��������Ҫ�½�һ��ͷ�ڵ�
			_root = new Node(-1, 1);
			_root->left = node;
			node->parent = _root;
			printf("�½�ͷ�ڵ� [%3d] tree_depth=%d, level=%d, data=%-6d\n",
				__LINE__, _root->level, _root->level, _root->data);
			return;
		}
		auto p = _findEmptyNode(_findLastNode(_root));

		if (p) {
			if (p->left->left == nullptr && p->right == nullptr) {
				p->right = node;
				node->parent = p;
				// ���¹�ϣֵ
				p->data = _hash(p->left->data, p->right->data);
			}
			else { // �м�ڵ㣬��Ҫ�����������½���������ͬ�����
				auto l = p->level - 1;
				auto tmp = new Node(-1, l);
				p->right = tmp;
				tmp->parent = p;
				printf("���м�ڵ� [%3d] tree_depth=%d, level=%d, data=%-6d\n",
					__LINE__, _root->level, tmp->level, tmp->data);

				p = p->right;
				l = p->level - 1; // ����level - 1

				while (l > 0) {
					tmp = new Node(-1, l);
					p->left = tmp;
					tmp->parent = p;
					printf("���м�ڵ� [%3d] tree_depth=%d, level=%d, data=%-6d\n",
						__LINE__, _root->level, tmp->level, tmp->data);

					p = p->left;
					--l;
				}
				// Ҷ�ӽڵ㸳ֵ
				p->left = node;
				node->parent = p;

				// �Ե����ϸ��¹�ϣֵ
				while (p != _root) {
					p->data = _hash(p->left->data, p->right == nullptr ? 0 : p->right->data);
					p = p->parent;
				}
				// ���¸��ڵ��ϣֵ
				p->data = _hash(p->left->data, p->right == nullptr ? 0 : p->right->data);
			}
		}
		else { // �Ѿ������������ˣ���Ҫ����ͷ�ڵ㣬levelҲҪ��1
			auto tmp = _root;

			_root = new Node(-1, tmp->level + 1);
			_root->left = tmp;
			tmp->parent = _root;
			printf("�½�ͷ�ڵ� [%3d] tree_depth=%d, level=%d, data=%-6d\n",
				__LINE__, _root->level, _root->level, _root->data);

			// ����ͷ�ڵ�ĵ�һ��right�ӽڵ�
			tmp = new Node(-1, _root->level - 1);
			_root->right = tmp;
			tmp->parent = _root;
			printf("���м�ڵ� [%3d] tree_depth=%d, level=%d, data=%-6d\n",
				__LINE__, _root->level, tmp->level, tmp->data);

			// �����￪ʼ�����µ�����
			p = _root->right;
			auto l = p->level - 1;

			// ����������ȴ���ͬ�����������
			while (l > 0) {
				tmp = new Node(-1, l);
				p->left = tmp;
				tmp->parent = p;
				printf("���м�ڵ� [%3d] tree_depth=%d, level=%d, data=%-6d\n",
					__LINE__, _root->level, tmp->level, tmp->data);

				p = p->left;
				--l;
			}
			// Ҷ�ӽڵ㸳ֵ
			p->left = node;
			node->parent = p;

			// �Ե����ϸ��¹�ϣֵ
			while (p != _root) {
				p->data = _hash(p->left->data, p->right == nullptr ? 0 : p->right->data);
				p = p->parent;
			}
			// ���¸��ڵ��ϣֵ
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
		printf("Merkle Tree ������ϣ�����\n");
	}

	void _deleteMerkleTree(Node* p) {
		if (!p) return;
		if (!p->left && !p->right) {
			printf("����Ҷ�ӽڵ� [%3d] level=%d, data=%d\n", __LINE__, p->level, p->data);
			delete p;
			return;
		}
		_deleteMerkleTree(p->left);
		_deleteMerkleTree(p->right);
		printf("�����м�ڵ� [%3d] level=%d, data=%d\n", __LINE__, p->level, p->data);
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
		if (!mt->left && !mt->right) // Ҷ�ӽڵ�
			return mt;
		if (mt->right) // �����Ҷ���
			return _findLastNode(mt->right);
		return _findLastNode(mt->left); // ֻ�������
	}

	Node* _findEmptyNode(Node* mt) {
		auto p = mt->parent;
		while (p->parent && p->left && p->right)
			p = p->parent;
		if (!p->parent && p->left && p->right) // ������
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