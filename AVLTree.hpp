
#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <queue>
#include <algorithm>

using namespace std;

template<typename T>
class AVLTree {
public:
	template<typename T>
	struct Node {
		T key;
		int height;
		Node<T>* lchild;
		Node<T>* rchild;

		Node(T key, Node<T>* l = nullptr, Node<T>* r = nullptr)
			: key(key), lchild(l), rchild(r) {}
	};
	AVLTree() : root(nullptr) {}
	~AVLTree() { destroy(); }

	void preOrder() {
		_preOrder(root);
	}
	
	void inOrder() {
		_inOrder(root);
	}
	
	void postOrder() {
		_postOrder(root);
	}

	void print() { // 打印
		_print(root);
	}
	
	void destroy() { // 销毁
		_destroy(root);
	}

	void insert(T key) { // 插入
		_insert(root, key);
	}
	
	void remove(T key) { // 删除
		_remove(root, key);
	}

	Node<T>* searchRecurse(T key) { // 递归找节点
		return _searchRecurse(root, key);
	}
	
	Node<T>* searchIterator(T key) { // 迭代找节点
		return _searchIterator(root, key);
	}

	T minimum() {
		return _minimum(root)->key;
	}
	
	T maximum() {
		return _maximum(root)->key;
	}

	int height() { return _height(root); }

private:
	Node<T>* root; // AVL树的根节点

private:
	void _visit(Node<T>* node) const {
		cout << node->key << endl;
	}

	void _preOrder(Node<T>* node) const {
		if (!node) return;
		_preOrder(node->lchild);
		_visit(node);
		_preOrder(node->lchild);
	}
	
	void _inOrder(Node<T>* node) const {
		if (!node) return;
		_inOrder(node->lchild);
		_visit(node);
		_inOrder(node->rchild);
	}
	
	void _postOrder(Node<T>* node) const {
		if (!node) return;
		_postOrder(node->lchild);
		_visit(node);
		_postOrder(node->rchild);
	}

	void _print(Node<T>* node) const {
		_preOrder(node);
		_inOrder(node);
		_postOrder(node);
	}

	void _destroy(Node<T>* node) {
		if (!node)
			return;
		_destroy(node->lchild);
		_destroy(node->rchild);
		delete node;
		node = nullptr;
	}

	Node<T>* _insert(Node<T>*& node, T key) {
		if (!node)
			node = new Node<T>(key);
		else if (key > node->key) {
			node->rchild = _insert(node->rchild, key);
			// 插入后失去平衡
			if (_height(node->rchild) - _height(node->lchild) == 2) {
				if (key > node->rchild->key) // 插入右子树的右节点，左旋
					node = _leftRotation(node);
				else if (key < node->rchild->key) // 插入右子树的左节点，先右旋再左旋
					node = _rightLeftRotation(node);
			}
		}
		else if (key < node->key) {
			node->rchild = _insert(node->lchild, key);
			if (_height(node->lchild) - _height(node->rchild) == 2) {
				if (key < node->lchild->key) // 插入左子树的左节点，右旋
					node = _rightRotation(node);
				else if (key > node->lchild->key) // 插入左子树的右节点，先左旋再右旋
					node = _leftRightRotation(node);
			}
		}
		node->height = max(_height(node->lchild), _height(node->rchild)) + 1;
		return node;
	}

	Node<T>* _remove(Node<T>*& node, T key) {
		if (!node)
			return nullptr;
		if (key == node->key) { // 找到要删除的节点
			// 左子树比右子树高，从左子树上选择最大的节点进行替换
			if (node->lchild && node->rchild) {
				if (_height(node->lchild) > _height(node->rchild)) {
					auto pre = _maximum(node->lchild);
					node->key = pre->key;
					node->lchild = _remove(node->lchild, pre->key); // 递归删除左子树的最大节点
				}
				else {
					auto pre = _maximum(node->rchild);
					node->key = pre->key;
					node->rchild = _remove(node->rchild, pre->key); // 递归删除右子树的最大节点
				}
			}
			else {
				auto tmp = node;
				if (node->lchild)
					node = node->lchild;
				else
					node = node->rchild;
				delete tmp;
				return nullptr;
			}
		}
		else if (key < node->key) { // 要删除的节点比当前节点小，在左子树上删除
			node->lchild = _remove(node->lchild, key);
			// 删除左子树节点导致不平衡
			if (_height(node->rchild) - _height(node->lchild) == 2) {
				if (_height(node->rchild->lchild) > _height(node->rchild->rchild))
					node = _rightLeftRotation(node);
				else
					node = _leftRotation(node);
			}
		}
		else if (key > node->key) { // 要删除的节点比当前节点大，在右子树上删除
			node->rchild = _remove(node->rchild, key);
			// 删除右子树节点导致不平衡
			if (_height(node->lchild) - _height(node->rchild) == 2) {
				if (_height(node->lchild->rchild) > _height(node->lchild->lchild))
					node = _leftRightRotation(node);
				else
					node = _rightRotation(node);
			}
		}
		return node;
	}

	Node<T>* _minimum(Node<T>* node) const {
		if (!node)
			return nullptr;
		while (node->lchild)
			node = node->lchild;
		return node;
	}
	
	Node<T>* _maximum(Node<T>* node) const {
		if (!node)
			return nullptr;
		while (node->rchild)
			node = node->rchild;
		return node;
	}

	Node<T>* _searchRecurse(Node<T>* node, T key) const {
		if (!node)
			return nullptr;
		if (key == node->key)
			return node;
		if (key < node->key)
			return _searchRecurse(node->lchild, key);
		return _searchRecurse(node->rchild, key);
	}

	Node<T>* _searchIterator(Node<T>* node, T key) const {
		if (!node)
			return nullptr;
		queue<Node<T>*> que;
		que.push(node);
		while (que.size()) {
			auto tmp = que.front();
			que.pop();
			if (tmp->key == key)
				return tmp;
			if (key < tmp->key && tmp->lchild)
				que.push(tmp->lchild);
			else if (key > tmp->key && tmp->rchild)
				que.push(tmp->rchild);
		}
		return nullptr;
	}

	Node<T>* _leftRotation(Node<T>* node) { // 单旋：左旋
		auto right = node->rchild;
		node->rchild = right->lchild;
		right->lchild = node;
		
		node->height = max(_height(node->lchild), _height(node->rchild)) + 1;
		right->height = max(_height(right->lchild), _height(right->rchild)) + 1;

		return right;
	}

	Node<T>* _rightRotation(Node<T>* node) { // 单旋：右旋
		auto left = node->lchild;
		node->lchild = left->rchild;
		left->rchild = node;

		node->height = max(_height(node->lchild), _height(node->rchild)) + 1;
		left->height = max(_height(left->lchild), _height(left->lchild)) + 1;

		return left;
	}
	
	Node<T>* _leftRightRotation(Node<T>* node) { // 双旋：先左后右，妙啊
		node->lchild = _leftRotation(node->lchild);
		return _rightRotation(node);
	}
	
	Node<T>* _rightLeftRotation(Node<T>* node) { // 双旋：先右后左
		node->rchild = _rightRotation(node->rchild);
		return _leftRotation(node);
	}

	int _height(Node<T>* node) {
		if (!node)
			return 0;
		return node->height;
	}
};

#endif