#include <iostream>
#include <assert.h>

#define SIZE 100

#include <abstract.h>

#include <array_stack.h>
#include <linked_stack.h>
#include "stack_test.h"

int main() {
	structures::ArrayStack<int> as{SIZE};
	std::cout << "testing ArrayStack  ... ";
	std::cout.flush();
	test_stack(&as);
	std::cout << "OK" << std::endl;

	structures::LinkedStack<int> ls{};
	std::cout << "testing LinkedStack ... ";
	std::cout.flush();
	test_stack(&ls);
	std::cout << "OK" << std::endl;
}

