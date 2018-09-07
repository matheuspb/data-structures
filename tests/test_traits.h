#ifndef TRAITS_H
#define TRAITS_H

#include <type_traits>

#include <array_list.h>
#include <avl_tree.h>
#include <binary_tree.h>
#include <doubly_circular_list.h>
#include <hash_table.h>
#include <linked_list.h>
#include <rb_tree.h>

namespace traits {

template <template <typename> class S>
struct is_list {
	const static bool value =
		std::is_same<S<void>, structures::ArrayList<void>>::value ||
		std::is_same<S<void>, structures::LinkedList<void>>::value ||
		std::is_same<S<void>, structures::DoublyCircularList<void>>::value;
};

template <template <typename> class S>
struct is_set {
	const static bool value =
		std::is_same<S<void>, structures::BinaryTree<void>>::value ||
		std::is_same<S<void>, structures::AVLTree<void>>::value ||
		std::is_same<S<void>, structures::RBTree<void>>::value ||
		std::is_same<S<void>, structures::HashTable<void>>::value;
};

}  // namespace traits

#endif
