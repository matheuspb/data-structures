#include <iostream>

#include "tests.h"

#include <array_list.h>
#include <avl_tree.h>
#include <binary_tree.h>
#include <doubly_circular_list.h>
#include <hash_table.h>
#include <heap.h>
#include <linked_list.h>
#include <queue.h>
#include <rb_tree.h>
#include <stack.h>

int main() {
	tests::test_structures<
		structures::ArrayList, structures::LinkedList,
		structures::DoublyCircularList, structures::Stack, structures::Queue,
		structures::BinaryTree, structures::AVLTree, structures::RBTree,
		structures::HashTable, structures::Heap>();
}
