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
	tests::test_stack<structures::ArrayStack<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing LinkedStack         ... ";
	std::cout.flush();
	tests::test_stack<structures::LinkedStack<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing ArrayQueue          ... ";
	std::cout.flush();
	tests::test_queue<structures::ArrayQueue<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing LinkedQueue         ... ";
	std::cout.flush();
	tests::test_queue<structures::LinkedQueue<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing ArrayList           ... ";
	std::cout.flush();
	tests::test_list<structures::ArrayList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing LinkedList          ... ";
	std::cout.flush();
	tests::test_list<structures::LinkedList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing DoublyLinkedList    ... ";
	std::cout.flush();
	tests::test_list<structures::DoublyLinkedList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing CircularList        ... ";
	std::cout.flush();
	tests::test_list<structures::CircularList<int>>();
	std::cout << "OK" << std::endl;

	std::cout << "testing DoublyCircularList  ... ";
	std::cout.flush();
	tests::test_list<structures::DoublyCircularList<int>>();
	std::cout << "OK" << std::endl;
}

