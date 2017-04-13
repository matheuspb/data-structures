#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <iostream>
#include "tree.h"

namespace structures {

template<typename T> class AVLNode;

/**
@brief BinaryTree node implementation
*/
template<typename T>
class Node {

	friend class AVLNode<T>;

public:

	explicit Node(const T& data_):
		data{data_} {}

	Node(const T& data_, Node* parent_):
		data{data_},
		parent{parent_} {}

	~Node() {
		delete left;
		delete right;
	}

	virtual Node* insert(const T& data_) {
		if (data_ < data) {
			// insert left
			if (left) {
				return left->insert(data_);
			} else {
				left = new Node(data_, this);
				return left;
			}
		} else {
			// insert right
			if (right) {
				return right->insert(data_);
			} else {
				right = new Node(data_, this);
				return right;
			}
		}
	}

	virtual Node* remove(const T& data_) {
		if (data == data_) {
			if (right && left) {
				data = substitute();
				right->remove(data);
			} else {
				auto n = right ? right : left;

				if (parent->right == this) {
					parent->right = n;
				} else {
					parent->left = n;
				}

				if (n)
					n->parent = parent;

				delete this;
			}
			return parent;
		} else {
			auto n = data_ < data ? left : right;
			return n ? n->remove(data_) : nullptr;
		}
	}

	bool contains(const T& data_) const {
		if (data == data_) {
			return true;
		} else {
			if (data_ < data) {
				return left ? left->contains(data_) : false;
			} else {
				return right ? right->contains(data_) : false;
			}
		}
	}

	void pre_order(ArrayList<T>& v) const {
		v.push_back(data);
		if (left)
			left->pre_order(v);
		if (right)
			right->pre_order(v);
	}

	void in_order(ArrayList<T>& v) const {
		if (left)
			left->in_order(v);
		v.push_back(data);
		if (right)
			right->in_order(v);
	}

	void post_order(ArrayList<T>& v) const {
		if (left)
			left->post_order(v);
		if (right)
			right->post_order(v);
		v.push_back(data);
	}

	// returns the smallest value of the right sub-tree
	T substitute() const {
		Node* it = right;
		while (it->left) {
			it = it->left;
		}
		return it->data;
	}

	void print(int indent) const {
		if (right)
			right->print(indent + 1);
		for (int i = 0; i < indent; ++i)
			std::cout << "    ";
		std::cout << data << std::endl;
		if (left)
			left->print(indent + 1);
	}

private:

	T data{};
	Node* parent{nullptr};
	Node* left{nullptr};
	Node* right{nullptr};
	std::size_t height{1u};

};

/**
@brief Unbalanced binary search tree

@details This structure provides O(log(n)) operations on the best case, but as
it is unbalanced, the operations may be O(n) on the worst case (e.g. you insert
members in order).
*/
template<typename T>
class BinaryTree : public Tree<T, Node<T>> {};

}  // namespace structures

#endif
