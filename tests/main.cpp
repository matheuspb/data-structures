#include <iostream>

#include "tests.h"

#include <array_list.h>
#include <queue.h>
#include <stack.h>
#include <avl_tree.h>
#include <binary_tree.h>
#include <doubly_circular_list.h>
#include <hash_table.h>
#include <heap.h>
#include <linked_list.h>
#include <rb_tree.h>

int main() {
	std::cout << "testing Stack<ArrayList<T>> ... ";
	std::cout.flush();
	tests::test_stack<structures::Stack<int, structures::ArrayList<int>>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Stack<LinkedList<T>>... ";
	std::cout.flush();
	tests::test_stack<structures::Stack<int, structures::LinkedList<int>>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Queue<ArrayList<T>> ... ";
	std::cout.flush();
	tests::test_queue<structures::Queue<int, structures::ArrayList<int>>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Queue<LinkedList<T>>... ";
	std::cout.flush();
	tests::test_queue<structures::Queue<int, structures::LinkedList<int>>>();
	std::cout << "OK" << std::endl;

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

	std::cout << "testing HashTable           ... ";
	std::cout.flush();
	tests::test_structure<structures::HashTable<double>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing BinaryTree          ... ";
	std::cout.flush();
	tests::test_structure<structures::BinaryTree<double>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing AVLTree             ... ";
	std::cout.flush();
	tests::test_structure<structures::AVLTree<double>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing RBTree              ... ";
	std::cout.flush();
	tests::test_structure<structures::RBTree<double>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Heap                ... ";
	std::cout.flush();
	tests::test_structure<structures::Heap<int>>();
	std::cout << "OK" << std::endl;
}
