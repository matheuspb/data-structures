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
	tests::test_structure<structures::ArrayList>();
	std::cout << "OK" << std::endl;

	std::cout << "testing LinkedList          ... ";
	std::cout.flush();
	tests::test_structure<structures::LinkedList>();
	std::cout << "OK" << std::endl;

	std::cout << "testing DoublyCircularList  ... ";
	std::cout.flush();
	tests::test_structure<structures::DoublyCircularList>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Stack               ... ";
	std::cout.flush();
	tests::test_structure<structures::Stack>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Queue               ... ";
	std::cout.flush();
	tests::test_structure<structures::Queue>();
	std::cout << "OK" << std::endl;

	std::cout << "testing BinaryTree          ... ";
	std::cout.flush();
	tests::test_structure<structures::BinaryTree>();
	std::cout << "OK" << std::endl;

	std::cout << "testing AVLTree             ... ";
	std::cout.flush();
	tests::test_structure<structures::AVLTree>();
	std::cout << "OK" << std::endl;

	std::cout << "testing RBTree              ... ";
	std::cout.flush();
	tests::test_structure<structures::RBTree>();
	std::cout << "OK" << std::endl;

	std::cout << "testing HashTable           ... ";
	std::cout.flush();
	tests::test_structure<structures::HashTable>();
	std::cout << "OK" << std::endl;

	std::cout << "testing Heap                ... ";
	std::cout.flush();
	tests::test_structure<structures::Heap>();
	std::cout << "OK" << std::endl;
}
