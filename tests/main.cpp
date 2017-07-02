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
}
