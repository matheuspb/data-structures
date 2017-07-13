#ifndef STRUCTURES_RB_TREE_H
#define STRUCTURES_RB_TREE_H

#include "avl_tree.h"
#include "binary_tree.h"
#include <cassert>

namespace structures {

/**
 * @brief RBTree node implementation
 */
template <typename T>
class RBNode : public Node<T> {
	template <typename U>
	friend class RBTree;

private:
	typedef enum { red, black } Color;

public:
	explicit RBNode(const T& data_) : Node<T>{data_} {}

	RBNode(const T& data_, Node<T>* parent_, Color c)
		: Node<T>{data_, parent_}, color{c} {}

	static RBNode<T>* insert(RBNode<T>* node, const T& data_) {
		auto new_node = Node<T>::insert(node, data_);

		if (new_node == nullptr)
			return nullptr;

		RBNode<T>* new_rb_node = new RBNode<T>(data_, new_node->parent, red);

		if (new_rb_node->parent->right == new_node) {
			new_rb_node->parent->right = new_rb_node;
		} else {
			new_rb_node->parent->left = new_rb_node;
		}

		delete new_node;

		update_ins(new_rb_node);
		return new_rb_node;
	}

	static RBNode<T>* remove(RBNode<T>* node, const T& data_) {
		auto to_delete = (RBNode<T>*) node->find_node_to_delete(data_);
		if (to_delete) {
			auto p = to_delete->parent;
			del_and_update(to_delete);
			return (RBNode<T>*) p;
		} else {
			return nullptr;
		}
	}

	void print(int indent) const {
		if (this->right)
			this->right->print(indent + 1);
		for (int i = 0; i < indent; ++i)
			std::cout << "    ";
		std::cout << (color == red ? "R " : "B ") << this->data << std::endl;
		if (this->left)
			this->left->print(indent + 1);
	}

private:
	static void recolor(RBNode<T>* n) {
		if (n) {
			n->color = n->color == red ? black : red;
		}
	}

	static Color node_color(RBNode<T>* n) { return n ? n->color : black; }

	static RBNode<T>* grandparent(RBNode<T>* n) {
		assert(n->parent->parent != nullptr);
		return (RBNode*) n->parent->parent;
	}

	static RBNode<T>* sibling(RBNode<T>* n) {
		if (n == n->parent->left) {
			return (RBNode*) n->parent->right;
		} else {
			return (RBNode*) n->parent->left;
		}
	}

	static RBNode<T>* uncle(RBNode<T>* n) {
		return sibling((RBNode*) n->parent);
	}

	static bool left_child(Node<T>* n) { return n == n->parent->left; }

	static void update_ins(RBNode<T>* x) {
		if (x->parent == nullptr) {
			x->color = black;
		} else {
			if (((RBNode*) x->parent)->color == red) {
				if (node_color(uncle(x)) == red) {
					recolor((RBNode*) x->parent);
					recolor(uncle(x));
					recolor(grandparent(x));
					update_ins(grandparent(x));
				} else {
					if (left_child(x->parent)) {
						if (!left_child(x))
							AVLNode<T>::simpleLeft(x->parent);
						AVLNode<T>::simpleRight(grandparent(x));
					} else {
						if (left_child(x))
							AVLNode<T>::simpleRight(x->parent);
						AVLNode<T>::simpleLeft(grandparent(x));
					}
				}
			}
		}
	}

	static void del_and_update(RBNode<T>* n) {
		auto child = n->left ? n->left : n->right;

		if (n->color == red || node_color((RBNode<T>*) child) == red) {
			if (child)
				((RBNode<T>*) child)->color = black;
		} else {
			auto s = sibling(n);

			if (s == nullptr) {
				double_black_case((RBNode<T>*) n->parent);
			} else if (node_color(s) == black) {
				if (node_color((RBNode<T>*) s->left) == black &&
					node_color((RBNode<T>*) s->right) == black) {
					black_nephews_case(s);
				} else {
					double_black_case(n);
				}
			} else {
				if (left_child(s)) {
					AVLNode<T>::simpleRight(n->parent);
					double_black_case(n);
				} else {
					AVLNode<T>::simpleLeft(n->parent);
					double_black_case(n);
				}
			}
		}

		if (left_child(n)) {
			n->parent->left = child;
		} else {
			n->parent->right = child;
		}

		if (child) {
			child->parent = n->parent;
		}

		n->left = nullptr;
		n->right = nullptr;
		delete n;
	}

	static void black_nephews_case(RBNode<T>* sib) {
		sib->color = red;
		RBNode<T>* p = (RBNode<T>*) sib->parent;
		if (p->color == black)
			double_black_case(p);
		else
			p->color = black;
	}

	static void double_black_case(RBNode<T>* n) {
		if (n->parent == nullptr)  // root node
			return;

		auto s = sibling(n);

		if (s == nullptr) {
			return double_black_case((RBNode<T>*) n->parent);
		}

		if (node_color((RBNode<T>*) s->left) == black &&
			node_color((RBNode<T>*) s->right) == black) {
			return black_nephews_case(s);
		}

		if (left_child(s)) {
			if (node_color((RBNode<T>*) s->right) == red) {
				AVLNode<T>::simpleLeft(s);
			}

			recolor((RBNode<T>*) s->left);
			s->color = ((RBNode<T>*) s->parent)->color;
			((RBNode<T>*) s->parent)->color = black;

			AVLNode<T>::simpleRight(s->parent);
			std::swap(
				((RBNode<T>*) s->parent)->color,
				((RBNode<T>*) s->parent->right)->color);
		} else {
			if (node_color((RBNode<T>*) s->left) == red) {
				AVLNode<T>::simpleRight(s);
			}

			recolor((RBNode<T>*) s->right);
			s->color = ((RBNode<T>*) s->parent)->color;
			((RBNode<T>*) s->parent)->color = black;

			AVLNode<T>::simpleLeft(s->parent);
			std::swap(
				((RBNode<T>*) s->parent)->color,
				((RBNode<T>*) s->parent->left)->color);
		}
	}

	Color color{black};
};

/**
 * @brief A self-balancing tree
 *
 * @details This tree, like the AVL, rotates itself to keep balanced and
 * guarantee O(log n) on all cases. But it has some different properties that
 * makes the tree rotate less than the AVL, so it keeps balanced and has faster
 * insert and removal operations than the AVL tree.
 *
 * The balancing of the tree is not perfect, but it is good enough to allow it
 * to guarantee searching in O(log n) time.
 */
template <typename T>
class RBTree : public Tree<T, RBNode<T>> {
public:
	bool remove(const T& data) {
		bool r = Tree<T, RBNode<T>>::remove(data);
		if (this->root) {
			this->root->color = RBNode<T>::black;
		}
		return r;
	}
};
}

#endif
