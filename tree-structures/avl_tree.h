#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <iostream>
#include <algorithm>
#include "../array-structures/array_list.h"

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
		delete root;
	}

	/**
	@brief Inserts 'data' into the tree
	*/
	void insert(const T& data) {
		if (root) {
			root->insert(data);
		} else {
			root = new Node(data);
		}
		++size_;
	}

	/**
	@brief Removes 'data' from the tree, if it exists in the tree
	*/
	void remove(const T& data) {
		if (root) {
			if (root->data == data) {
				if (root->right && root->left) {
					root->data = root->substitute();
					root->right->remove(root->data);
				} else {
					Node* n = root->right ? root->right : root->left;

					delete root;
					root = n;
					if (root)
						root->parent = nullptr;
				}
				--size_;
			} else if (root->remove(data)) {
				--size_;
			}
		}
	}

	/**
	@brief Returns true if the tree contains 'data'
	*/
	bool contains(const T& data) const {
		return root ? root->contains(data) : false;
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
		ArrayList<T> out{size_};
		if (root)
			root->pre_order(out);
		return out;
	}

	/**
	@brief Returns a in-ordered list of the tree
	*/
	ArrayList<T> in_order() const {
		ArrayList<T> out{size_};
		if (root)
			root->in_order(out);
		return out;
	}

	/**
	@brief Returns a post-ordered list of the tree
	*/
	ArrayList<T> post_order() const {
		ArrayList<T> out{size_};
		if (root)
			root->post_order(out);
		return out;
	}

	/**
	@brief Prints the tree sideways
	*/
	void print() const {
		std::cout << "Tree size = " << size_;
		if (root) {
			std::cout << ", height = " << root->height;
			std::cout << std::endl << std::endl;
			root->print(0);
			for (int i = 0; i < 80; ++i) {
				std::cout << "-";
			}
		}
		std::cout << std::endl;
	}

private:
	struct Node {
		explicit Node(const T& data_):
			data{data_} {}

		Node(const T& data_, Node* parent_):
			data{data_},
			parent{parent_} {}

		~Node() {
			delete left;
			delete right;
		}

		void insert(const T& data_) {
			if (data_ < data) {
				// insert left
				if (left) {
					left->insert(data_);
				} else {
					left = new Node(data_, this);
				}
			} else {
				// insert right
				if (right) {
					right->insert(data_);
				} else {
					right = new Node(data_, this);
				}
			}
			update();
		}

		bool remove(const T& data_) {
			bool removed;
			if (data == data_) {
				if (right && left) {
					data = substitute();
					right->remove(data);
				} else {
					Node* n = right ? right : left;

					if (parent->right == this) {
						parent->right = n;
					} else {
						parent->left = n;
					}

					if (n)
						n->parent = parent;

					delete this;
				}
				removed = true;
			} else {
				Node* n = data_ < data ? left : right;
				removed = n ? n->remove(data_) : false;
				if (removed)
					update();
			}
			return removed;
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

		void updateHeight() {
			int rh = right ? right->height : 0;
			int lh = left ? left->height : 0;
			height = std::max(rh, lh) + 1;
		}

		void update() {
			updateHeight();

			// rotates if needed
			if (getBF() < -1) {
				// node is left heavy
				if (left->getBF() > 0)
					left->rotateLeft();
				rotateRight();
			} else if (getBF() > 1) {
				// node is right heavy
				if (right->getBF() < 0)
					right->rotateRight();
				rotateLeft();
			}
		}

		// Returns the balance factor
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

		// Updates sons' parent pointer
		void updateSons() {
			if (left)
				left->parent = this;
			if (right)
				right->parent = this;
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
