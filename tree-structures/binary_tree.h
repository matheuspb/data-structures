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
	@brief Destructor
	*/
	~BinaryTree() {
		while (!empty()) {
			remove(root->data);
		}
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
	@brief Removes 'data' from the tree
	*/
	void remove(const T& data) {
		if (root == nullptr) {
			return;
		} else if (root->data == data) {
			if (root->left == nullptr) {
				Node* oldRoot = root;
				root = root->right;
				delete oldRoot;
			} else if (root->right == nullptr) {
				Node* oldRoot = root;
				root = root->left;
				delete oldRoot;
			} else {
				Node* it = root->right;
				while (it->left != nullptr) {
					it = it->left;
				}
				root->data = it->data;
				root->remove(it->data);
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
		Node(const T& data_):
			data{data_}
		{}

		void insert(const T& data_) {
			if (data_ < data) {
				// insert left
				if (left == nullptr) {
					left = new Node(data_);
				} else {
					left->insert(data_);
				}
			} else {
				// insert right
				if (right == nullptr) {
					right = new Node(data_);
				} else {
					right->insert(data_);
				}
			}
		}

		bool remove(const T& data_) {
			if (left != nullptr && data_ == left->data) {
				if (left->right == nullptr) {
					Node* oldLeft = left;
					left = left->left;
					delete oldLeft;
				} else if (left->left == nullptr) {
					Node* oldLeft = left;
					left = left->right;
					delete oldLeft;
				} else {
					Node* it = left->right;
					while (it->left != nullptr) {
						it = it->left;
					}
					left->data = it->data;
					left->remove(it->data);
				}
				return true;
			} else if (right != nullptr && data_ == right->data) {
				if (right->right == nullptr) {
					Node* oldRight = right;
					right = right->left;
					delete oldRight;
				} else if (right->left == nullptr) {
					Node* oldRight = right;
					right = right->right;
					delete oldRight;
				} else {
					Node* it = right->right;
					while (it->left != nullptr) {
						it = it->left;
					}
					right->data = it->data;
					right->remove(it->data);
				}
				return true;
			} else if (data_ < data) {
				if (left != nullptr)
					return left->remove(data_);
				else
					return false;
			} else {
				if (right != nullptr)
					return right->remove(data_);
				else
					return false;
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

		T data;
		Node* left{nullptr};
		Node* right{nullptr};
	};

	Node* root{nullptr};
	std::size_t size_{0u};
};

}

#endif
