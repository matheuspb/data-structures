// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "../array-structures/array_list.h"
#include <iostream>
#include <algorithm>

namespace structures {

/**
@brief Implements an AVL tree
*/
template<typename T>
class AVLTree {
public:
	/**
	@brief Destructor
	*/
	~AVLTree() {
		if (root != nullptr)
			root->destruct();
	}

	/**
	@brief Inserts 'data' into the tree
	*/
	void insert(const T& data) {
		if (root == nullptr) {
			root = new Node(data);
		} else {
			root->insert(data);
		}
		++size_;
	}

	/**
	@brief Removes 'data' from the tree, if it exists in the tree
	*/
	void remove(const T& data) {
		if (root == nullptr) {
			return;
		} else if (root->data == data) {
			if (root->left == nullptr) {
				if (root->right == nullptr) {
					delete root;
					root = nullptr;
				} else {
					Node* oldRoot = root;
					root = root->right;
					root->parent = nullptr;
					delete oldRoot;
				}
			} else if (root->right == nullptr) {
				Node* oldRoot = root;
				root = root->left;
				root->parent = nullptr;
				delete oldRoot;
			} else {
				root->data = root->substitute();
				root->right->remove(root->data);
			}
			--size_;
		} else if (root->remove(data)) {
			--size_;
		}
	}

	/**
	@brief Returns true if the tree contains 'data'
	*/
	bool contains(const T& data) const {
		if (root == nullptr)
			return false;
		else
			return root->contains(data);
	}

	/**
	@brief Returns true if the tree is empty
	*/
	bool empty() const {
		return size_ == 0;
	}

	/**
	@brief Returns the size of the tree
	*/
	std::size_t size() const {
		return size_;
	}

	/**
	@brief Returns a pre-ordered list of the tree
	*/
	ArrayList<T> pre_order() const {
		ArrayList<T> out(size_);
		if (root != nullptr)
			root->pre_order(out);
		return out;
	}

	/**
	@brief Returns a in-ordered list of the tree
	*/
	ArrayList<T> in_order() const {
		ArrayList<T> out(size_);
		if (root != nullptr)
			root->in_order(out);
		return out;
	}

	/**
	@brief Returns a post-ordered list of the tree
	*/
	ArrayList<T> post_order() const {
		ArrayList<T> out(size_);
		if (root != nullptr)
			root->post_order(out);
		return out;
	}

	/**
	@brief Prints the tree sideways
	*/
	void print() const {
		if (root != nullptr) {
			for (int i = 0; i < 80; ++i) {
				std::cout << "-";
			}
			std::cout << std::endl;
			root->print(0);
			for (int i = 0; i < 80; ++i) {
				std::cout << "-";
			}
			std::cout << std::endl;
		}
	}

private:
	struct Node {
		explicit Node(const T& data_):
			data{data_} {}

		Node(const T& data_, Node* parent_):
			data{data_},
			parent{parent_} {}

		void insert(const T& data_) {
			if (data_ < data) {
				// insert left
				if (left == nullptr) {
					left = new Node(data_, this);
				} else {
					left->insert(data_);
				}
			} else {
				// insert right
				if (right == nullptr) {
					right = new Node(data_, this);
				} else {
					right->insert(data_);
				}
			}
			update();
		}

		bool remove(const T& data_) {
			if (data == data_) {
				if (right == nullptr) {
					if (left == nullptr) {
						if (parent->right == this) {
							parent->right = nullptr;
						} else {
							parent->left = nullptr;
						}
					} else {
						if (parent->right == this) {
							parent->right = left;
						} else {
							parent->left = left;
						}
						left->parent = parent;
					}
					delete this;
				} else if (left == nullptr) {
					if (parent->right == this) {
						parent->right = right;
					} else {
						parent->left = right;
					}
					right->parent = parent;
					delete this;
				} else {
					data = substitute();
					right->remove(data);
				}
				return true;
			} else if (data_ < data) {
				if (left != nullptr && left->remove(data_)) {
					update();
					return true;
				} else {
					return false;
				}
			} else {
				if (right != nullptr && right->remove(data_)) {
					update();
					return true;
				} else {
					return false;
				}
			}
		}

		bool contains(const T& data_) const {
			if (data == data_) {
				return true;
			} else {
				if (data_ < data) {
					if (left == nullptr)
						return false;
					else
						return left->contains(data_);
				} else {
					if (right == nullptr)
						return false;
					else
						return right->contains(data_);
				}
			}
		}

		void pre_order(ArrayList<T>& v) const {
			v.push_back(data);
			if (left != nullptr)
				left->pre_order(v);
			if (right != nullptr)
				right->pre_order(v);
		}

		void in_order(ArrayList<T>& v) const {
			if (left != nullptr)
				left->in_order(v);
			v.push_back(data);
			if (right != nullptr)
				right->in_order(v);
		}

		void post_order(ArrayList<T>& v) const {
			if (left != nullptr)
				left->post_order(v);
			if (right != nullptr)
				right->post_order(v);
			v.push_back(data);
		}

		// returns the smallest value of the right sub-tree
		T substitute() const {
			Node* it = right;
			while (it->left != nullptr) {
				it = it->left;
			}
			return it->data;
		}

		void updateHeight() {
			int rh = right ? right->height : 0;
			int lh = left ? left->height : 0;
			height = std::max(rh, lh) + 1;
		}

		void update() {
			updateHeight();

			// rotates if needed
			if (getBF() < -1) {
				// left heavy
				if (left->getBF() > 0)
					left->rotateLeft();
				rotateRight();
			} else if (getBF() > 1) {
				// right heavy
				if (right->getBF() < 0)
					right->rotateRight();
				rotateLeft();
			}
		}

		// returns the balance factor
		int getBF() const {
			int rh = right ? right->height : 0;
			int lh = left ? left->height : 0;
			return rh - lh;
		}

		/* Rotations:
		*
		*     a       left       b
		*    / \     ----->     / \
		*   x   b              a   z
		*      / \    right   / \
		*     y   z  <-----  x   y
		*/
		void rotateRight() {
			std::swap(data, left->data);

			auto nleft = left->left;
			left->left = left->right;
			left->right = right;
			right = left;
			left = nleft;

			updateSons();
			right->updateSons();

			right->updateHeight();
			updateHeight();
		}

		void rotateLeft() {
			std::swap(data, right->data);

			auto nright = right->right;
			right->right = right->left;
			right->left = left;
			left = right;
			right = nright;

			updateSons();
			left->updateSons();

			left->updateHeight();
			updateHeight();
		}

		// updates sons parent pointer
		void updateSons() {
			if (left != nullptr)
				left->parent = this;
			if (right != nullptr)
				right->parent = this;
		}

		// Destructs the sub-tree
		void destruct() {
			if (left != nullptr)
				left->destruct();
			if (right != nullptr)
				right->destruct();
			delete this;
		}

		void print(int indent) const {
			if (right != nullptr)
				right->print(indent + 1);
			for (int i = 0; i < indent; ++i)
				std::cout << "    ";
			std::cout << data << std::endl;
			if (left != nullptr)
				left->print(indent + 1);
		}

		T data;
		Node* parent{nullptr};
		Node* left{nullptr};
		Node* right{nullptr};
		std::size_t height{1u};
	};

	Node* root{nullptr};
	std::size_t size_{0u};
};

}  // namespace structures

#endif
