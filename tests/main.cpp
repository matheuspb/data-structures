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
	std::cout << "testing ArrayList           ... ";
	std::cout.flush();
	tests::test_list<structures::ArrayList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing LinkedList          ... ";
	std::cout.flush();
	tests::test_list<structures::LinkedList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing DoublyCircularList  ... ";
	std::cout.flush();
	tests::test_list<structures::DoublyCircularList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Stack               ... ";
	std::cout.flush();
	tests::test_stack<structures::Stack<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Queue               ... ";
	std::cout.flush();
	tests::test_queue<structures::Queue<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing BinaryTree          ... ";
	std::cout.flush();
	tests::test_set<structures::BinaryTree<double>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing AVLTree             ... ";
	std::cout.flush();
	tests::test_set<structures::AVLTree<double>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing RBTree              ... ";
	std::cout.flush();
	tests::test_set<structures::RBTree<double>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing HashTable           ... ";
	std::cout.flush();
	tests::test_set<structures::HashTable<double>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Heap                ... ";
	std::cout.flush();
	tests::test_prio_queue<structures::Heap<int>>();
	std::cout << "OK" << std::endl;
}
