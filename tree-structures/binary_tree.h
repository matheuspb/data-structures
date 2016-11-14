// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "../array-structures/array_list.h"

namespace structures {

/**
@brief Implements a binary search tree
*/
template<typename T>
class BinaryTree {
public:
	/**
	@brief Default constructor
	*/
	BinaryTree() = default;

	/**
	@brief Destructor
	*/
	~BinaryTree() {
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
		root->pre_order(out);
		return out;
	}

	/**
	@brief Returns a in-ordered list of the tree
	*/
	ArrayList<T> in_order() const {
		ArrayList<T> out(size_);
		root->in_order(out);
		return out;
	}

	/**
	@brief Returns a post-ordered list of the tree
	*/
	ArrayList<T> post_order() const {
		ArrayList<T> out(size_);
		root->post_order(out);
		return out;
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
		}

		bool remove(const T& data_) {
			if (data == data_) {
				if (right == nullptr) {
					if (left == nullptr) {
						if (parent->right == this) {
							parent->right = nullptr;
							delete this;
						} else {
							parent->left = nullptr;
							delete this;
						}
					} else {
						if (parent->right == this) {
							parent->right = left;
							left->parent = parent;
							delete this;
						} else {
							parent->left = left;
							left->parent = parent;
							delete this;
						}
					}
				} else if (left == nullptr) {
					if (parent->right == this) {
						parent->right = right;
						right->parent = parent;
						delete this;
					} else {
						parent->left = right;
						right->parent = parent;
						delete this;
					}
				} else {
					data = substitute();
					right->remove(data);
				}
				return true;
			} else if (data_ < data) {
				if (left != nullptr && left->remove(data_)) {
					return true;
				} else {
					return false;
				}
			} else {
				if (right != nullptr && right->remove(data_)) {
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

		void destruct() {
			if (left != nullptr)
				left->destruct();
			if (right != nullptr)
				right->destruct();
			delete this;
		}

		T data;
		Node* parent{nullptr};
		Node* left{nullptr};
		Node* right{nullptr};
	};

	Node* root{nullptr};
	std::size_t size_{0u};
};

}  // namespace structures

#endif
