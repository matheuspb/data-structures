#include <iostream>

#include <tests.h>

#include <array_stack.h>
#include <linked_stack.h>

#include <array_queue.h>
#include <linked_queue.h>

#include <array_list.h>
#include <linked_list.h>
#include <doubly_linked_list.h>
#include <circular_list.h>
#include <doubly_circular_list.h>

#include <hash_table.h>
#include <binary_tree.h>
#include <avl_tree.h>
#include <rb_tree.h>

int main() {

	std::cout << "testing ArrayStack          ... ";
	std::cout.flush();
	tests::test_structure<structures::ArrayStack<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing LinkedStack         ... ";
	std::cout.flush();
	tests::test_structure<structures::LinkedStack<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing ArrayQueue          ... ";
	std::cout.flush();
	tests::test_structure<structures::ArrayQueue<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing LinkedQueue         ... ";
	std::cout.flush();
	tests::test_structure<structures::LinkedQueue<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing ArrayList           ... ";
	std::cout.flush();
	tests::test_structure<structures::ArrayList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing LinkedList          ... ";
	std::cout.flush();
	tests::test_structure<structures::LinkedList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing DoublyLinkedList    ... ";
	std::cout.flush();
	tests::test_structure<structures::DoublyLinkedList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing CircularList        ... ";
	std::cout.flush();
	tests::test_structure<structures::CircularList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing DoublyCircularList  ... ";
	std::cout.flush();
	tests::test_structure<structures::DoublyCircularList<int>>();
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

}
