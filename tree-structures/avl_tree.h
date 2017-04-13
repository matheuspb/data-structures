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

	static AVLNode<T>* insert(AVLNode<T>* node, const T& data_) {
		auto new_node = Node<T>::insert(node, data_);

		AVLNode<T>* new_avl_node = new AVLNode<T>(data_, new_node->parent);

		if (new_avl_node->parent->right == new_node) {
			new_avl_node->parent->right = new_avl_node;
		} else {
			new_avl_node->parent->left = new_avl_node;
		}

		update(new_avl_node);
		return new_avl_node;
	}

	static AVLNode<T>* remove(AVLNode<T>* node, const T& data_) {
		auto parent = (AVLNode<T>*) Node<T>::remove(node, data_);
		if (parent)
			update(parent);
		return parent;
	}

private:

	static void updateHeight(AVLNode<T>* n) {
		if (n) {
			int rh = n->right ? ((AVLNode<T>*) n->right)->height : 0;
			int lh = n->left ? ((AVLNode<T>*) n->left)->height : 0;
			n->height = std::max(rh, lh) + 1;
		}
	}

	static void update(AVLNode<T>* n) {
		if (n == nullptr) return;

		updateHeight(n);

		// rotates if needed
		if (getBF(n) < -1) {
			// node is left heavy
			if (getBF((AVLNode<T>*) n->left) > 0)
				rotateLeft((AVLNode<T>*) n->left);
			rotateRight(n);
		} else if (getBF(n) > 1) {
			// node is right heavy
			if (getBF((AVLNode<T>*) n->right) < 0)
				rotateRight((AVLNode<T>*) n->right);
			rotateLeft(n);
		}

		update((AVLNode<T>*) n->parent);
	}

	// Returns the balance factor
	static int getBF(AVLNode<T>* n) {
		int rh = n->right ? ((AVLNode<T>*) n->right)->height : 0;
		int lh = n->left ? ((AVLNode<T>*) n->left)->height : 0;
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
	static void rotateRight(AVLNode<T>* n) {
		std::swap(n->data, n->left->data);

		std::swap(n->left->left, n->left->right);
		std::swap(n->left->right, n->right);
		std::swap(n->right, n->left);

		updateSons(n);
		updateSons(n->right);

		updateHeight((AVLNode<T>*) n->right);
		updateHeight(n);
	}

	static void rotateLeft(AVLNode<T>* n) {
		std::swap(n->data, n->right->data);

		std::swap(n->right->right, n->right->left);
		std::swap(n->right->left, n->left);
		std::swap(n->left, n->right);

		updateSons(n);
		updateSons(n->left);

		updateHeight((AVLNode<T>*) n->left);
		updateHeight(n);
	}

	// Updates sons' parent pointer
	static void updateSons(Node<T>* n) {
		if (n->left)
			n->left->parent = n;
		if (n->right)
			n->right->parent = n;
	}

	std::size_t height{1u};

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
