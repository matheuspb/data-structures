#ifndef TREE_H
#define TREE_H

#include "../array-structures/array_list.h"

namespace structures {

/**
@brief Binary search tree basic operations are implemented here, the Node
implementations may be custom, e.g. you can use the AVLNode class to have an
AVLTree.

@tparam T Data type of the elements
@tparam N Class of the nodes of the tree
*/
template<typename T, typename N>
class Tree {

public:
	/**
	@brief Destructor
	*/
	~Tree() {
		delete root;
	}

	/**
	@brief Inserts 'data' into the tree
	*/
	void insert(const T& data) {
		if (root) {
			root->insert(data);
		} else {
			root = new N(data);
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
					auto n = root->right ? root->right : root->left;

					delete root;
					root = (N*) n;
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
			std::cout << std::endl << std::endl;
			root->print(0);
			for (int i = 0; i < 80; ++i) {
				std::cout << "-";
			}
		}
		std::cout << std::endl;
	}

private:
	N* root{nullptr};
	std::size_t size_{0u};

};

}  // namespace structures

#endif
