#include <iostream>

#include <tests.h>

#include <array_stack.h>
#include <linked_stack.h>

#include <array_queue.h>
#include <linked_queue.h>

int main() {
	{
		structures::ArrayStack<int> as{SIZE};
		std::cout << "testing ArrayStack  ... ";
		std::cout.flush();
		test_stack(&as);
		std::cout << "OK" << std::endl;
	}

	{
		structures::LinkedStack<int> ls{};
		std::cout << "testing LinkedStack ... ";
		std::cout.flush();
		test_stack(&ls);
		std::cout << "OK" << std::endl;
	}

	{
		structures::ArrayQueue<int> aq{SIZE};
		std::cout << "testing ArrayQueue  ... ";
		std::cout.flush();
		test_queue(&aq);
		std::cout << "OK" << std::endl;
	}

	{
		structures::LinkedQueue<int> lq{};
		std::cout << "testing LinkedQueue ... ";
		std::cout.flush();
		test_queue(&lq);
		std::cout << "OK" << std::endl;
	}
}

