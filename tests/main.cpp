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
	{
		structures::ArrayStack<int> as{SIZE};
		std::cout << "testing ArrayStack          ... ";
		std::cout.flush();
		test_stack(&as);
		std::cout << "OK" << std::endl;
	}

	{
		structures::LinkedStack<int> ls{};
		std::cout << "testing LinkedStack         ... ";
		std::cout.flush();
		test_stack(&ls);
		std::cout << "OK" << std::endl;
	}

	{
		structures::ArrayQueue<int> aq{SIZE};
		std::cout << "testing ArrayQueue          ... ";
		std::cout.flush();
		test_queue(&aq);
		std::cout << "OK" << std::endl;
	}

	{
		structures::LinkedQueue<int> lq{};
		std::cout << "testing LinkedQueue         ... ";
		std::cout.flush();
		test_queue(&lq);
		std::cout << "OK" << std::endl;
	}

	{
		structures::ArrayList<int> al{SIZE};
		std::cout << "testing ArrayList           ... ";
		std::cout.flush();
		test_list(&al);
		std::cout << "OK" << std::endl;
	}

	{
		structures::LinkedList<int> ll;
		std::cout << "testing LinkedList          ... ";
		std::cout.flush();
		test_list(&ll);
		std::cout << "OK" << std::endl;
	}

	{
		structures::DoublyLinkedList<int> dll;
		std::cout << "testing DoublyLinkedList    ... ";
		std::cout.flush();
			test_list(&dll);
		std::cout << "OK" << std::endl;
	}

	{
		structures::CircularList<int> cl;
		std::cout << "testing CircularList        ... ";
		std::cout.flush();
		test_list(&cl);
		std::cout << "OK" << std::endl;
	}

	{
		structures::DoublyCircularList<int> dcl;
		std::cout << "testing DoublyCircularList  ... ";
		std::cout.flush();
		test_list(&dcl);
		std::cout << "OK" << std::endl;
	}
}

