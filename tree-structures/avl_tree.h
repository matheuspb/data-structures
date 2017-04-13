#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <iostream>
#include <algorithm>
#include "binary_tree.h"

namespace structures {

/**
@brief AVLTree node implementation
*/
template<typename T>
class AVLNode : public Node<T> {

public:

	explicit AVLNode(const T& data_):
		Node<T>{data_} {}

	AVLNode(const T& data_, Node<T>* parent_):
		Node<T>{data_, parent_} {}

	Node<T>* insert(const T& data_) {
		auto new_node = Node<T>::insert(data_);
		update(new_node);
		return new_node;
	}

	Node<T>* remove(const T& data_) {
		auto parent = Node<T>::remove(data_);
		if (parent)
			update(parent);
		return parent;
	}

private:

	static void updateHeight(Node<T>* n) {
		int rh = n->right ? n->right->height : 0;
		int lh = n->left ? n->left->height : 0;
		n->height = std::max(rh, lh) + 1;
	}

	static void update(Node<T>* n) {
		if (n == nullptr) return;

		updateHeight(n);

		// rotates if needed
		if (getBF(n) < -1) {
			// node is left heavy
			if (getBF(n->left) > 0)
				rotateLeft(n->left);
			rotateRight(n);
		} else if (getBF(n) > 1) {
			// node is right heavy
			if (getBF(n->right) < 0)
				rotateRight(n->right);
			rotateLeft(n);
		}

		update(n->parent);
	}

	// Returns the balance factor
	static int getBF(Node<T>* n) {
		int rh = n->right ? n->right->height : 0;
		int lh = n->left ? n->left->height : 0;
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
	static void rotateRight(Node<T>* n) {
		std::swap(n->data, n->left->data);

		auto nleft = n->left->left;
		n->left->left = n->left->right;
		n->left->right = n->right;
		n->right = n->left;
		n->left = nleft;

		updateSons(n);
		updateSons(n->right);

		updateHeight(n->right);
		updateHeight(n);
	}

	static void rotateLeft(Node<T>* n) {
		std::swap(n->data, n->right->data);

		auto nright = n->right->right;
		n->right->right = n->right->left;
		n->right->left = n->left;
		n->left = n->right;
		n->right = nright;

		updateSons(n);
		updateSons(n->left);

		updateHeight(n->left);
		updateHeight(n);
	}

	// Updates sons' parent pointer
	static void updateSons(Node<T>* n) {
		if (n->left)
			n->left->parent = n;
		if (n->right)
			n->right->parent = n;
	}

};

/**
@brief Implements an AVL tree, a self balancing tree

@details This tree provides log(n) operations on all cases, because it rotates
as necessary to keep itself balanced.
*/
template<typename T>
class AVLTree : public Tree<T, AVLNode<T>> {};

}  // namespace structures

#endif
