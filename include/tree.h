#ifndef TREE_H
#define TREE_H

#include <array_list.h>

namespace structures {

/**
 * @brief Binary search tree basic operations are implemented here, the Node
 * implementations may be custom, e.g. you can use the AVLNode class to have an
 * AVLTree.
 *
 * @tparam T Data type of the elements
 * @tparam N Class of the nodes of the tree
 */
template <typename T, typename N>
class Tree : public Set<T> {
public:
	/**
	 * @brief Destructor
	 */
	~Tree() { delete root; }

	/**
	 * @brief Inserts 'data' into the tree
	 */
	bool insert(const T& data) {
		if (root) {
			if (!N::insert(root, data))
				return false;
		} else {
			root = new N(data);
		}
		++size_;
		return true;
	}

	/**
	 * @brief Removes 'data' from the tree, if it exists in the tree
	 */
	bool remove(const T& data) {
		if (root) {
			if (root->data == data) {
				if (root->right && root->left) {
					root->data = root->substitute();
					N::remove((N*) root->right, root->data);
				} else {
					N* n;
					if (root->right) {
						n = (N*) root->right;
						root->right = nullptr;  // Avoids recursive deletion
					} else {
						n = (N*) root->left;
						root->left = nullptr;  // Avoids recursive deletion
					}

					delete root;
					root = (N*) n;
					if (root)
						root->parent = nullptr;
				}
				--size_;
				return true;
			} else if (N::remove(root, data)) {
				--size_;
				return true;
			} else {
				return false;
			}
		}
		return false;
	}

	/**
	 * @brief Returns true if the tree contains 'data'
	 */
	bool contains(const T& data) const {
		return root ? root->contains(data) : false;
	}

	void clear() {
		while (size_ > 0)
			remove(root->data);
	}

	/**
	 * @brief Returns the size of the tree
	 */
	std::size_t size() const { return size_; }

	List<T>* items() const { return new ArrayList<T>(pre_order()); }

	/**
	 * @brief Returns a pre-ordered list of the tree
	 */
	ArrayList<T> pre_order() const {
		ArrayList<T> out{size_};
		if (root)
			root->pre_order(out);
		return out;
	}

	/**
	 * @brief Returns a in-ordered list of the tree
	 */
	ArrayList<T> in_order() const {
		ArrayList<T> out{size_};
		if (root)
			root->in_order(out);
		return out;
	}

	/**
	 * @brief Returns a post-ordered list of the tree
	 */
	ArrayList<T> post_order() const {
		ArrayList<T> out{size_};
		if (root)
			root->post_order(out);
		return out;
	}

	/**
	 * @brief Prints the tree sideways
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

protected:
	N* root{nullptr};
	std::size_t size_{0u};
};

}  // namespace structures

#endif
