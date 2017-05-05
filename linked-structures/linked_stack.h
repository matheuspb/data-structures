#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>

#include "linked_list.h"

namespace structures {

/**
 * @brief Implements a stack(data structure).
 * @details This data structure works just like a real 'stack', you add
 * elements to the top of the stack (push), and you remove from the top (pop).
 * It follows the 'LIFO' (last in, first out) principle.
 *
 * @tparam T This is the data type of the elements of the stack.
 */
template<typename T>
class LinkedStack : private LinkedList<T> {

public:

	using LinkedList<T>::clear;
	using LinkedList<T>::empty;
	using LinkedList<T>::size;

	/**
	 * @brief Adds 'data' to the top of the stack
	 *
	 * @param data The element that'll be added to the stack
	 */
	void push(const T& data) {
		LinkedList<T>::push_front(data);
	}

	/**
	 * @brief Removes the element at the top of the stack
	 *
	 * @return The element that was removed
	 */
	T pop() {
		if (empty()) {
			throw std::out_of_range("Stack is empty");
		} else {
			return LinkedList<T>::pop_front();
		}
	}

	/**
	 * @brief Returns the top element of the stack
	 *
	 * @return A reference to the top element of the stack
	 */
	const T& top() const {
		return this->at(0);
	}

};

}  // namespace structures

#endif
