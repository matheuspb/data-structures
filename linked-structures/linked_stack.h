// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
 * @brief Implements a stack(data structure).
 * @details This data structure works just like a real 'stack', you add elements
 * to the top of the stack (push), and you remove from the top (pop).
 * It follows the 'LIFO' (last in, first out) principle.
 *
 * @tparam T This is the data type of the elements of the stack.
 */
template<typename T>
class LinkedStack {
public:
	/**
	 * @brief Default constructor
	 */
	LinkedStack() = default;

	/**
	 * @brief Destructor
	 */
	~LinkedStack() {
		clear();
	}

	/**
	 * @brief Clears the stack
	 * @details Pops all elements of the list
	 */
	void clear() {
		while (!empty()) {
			pop();
		}
	}

	/**
	 * @brief Adds 'data' to the top of the stack
	 * @param data The element that'll be added to the stack
	 */
	void push(const T& data) {
		top_ = new Node(data, top_);
		++size_;
	}

	/**
	 * @brief Removes the element at the top of the stack
	 * @details Checks if the stack is not empty, then returns and removes the
	 * top element of the stack. Throws std::out_of_range if the stack is empty
	 *
	 * @return The element that was removed
	 */
	T pop() {
		if (empty())
			throw std::out_of_range("Stack is empty");

		auto toDelete = top_;
		top_ = top_->next();
		auto out = toDelete->data();
		delete toDelete;
		--size_;
		return out;
	}

	/**
	 * @brief Returns the top element of the stack
	 * @details Checks if stack is not empty, then returns the element at the
	 * top of the stack. Throws std::out_of_range if the stack is empty
	 *
	 * @return A reference to the top element of the stack
	 */
	T& top() const {
		if (empty())
			throw std::out_of_range("Stack is empty");
		return top_->data();
	}

	/**
	 * @brief Checks if stack is empty
	 * @return True if stack is empty
	 */
	bool empty() const {
		return size_ == 0;
	}

	/**
	 * @brief Returns the number of elements on the stack
	 */
	std::size_t size() const {
		return size_;
	}

private:
	class Node {
	public:
		explicit Node(const T& data): data_{data} {}
		Node(const T& data, Node* next): data_{data}, next_{next} {}

		T& data() {
			return data_;
		}

		const T& data() const {
			return data_;
		}

		Node* next() {
			return next_;
		}

		const Node* next() const {
			return next_;
		}

		void next(Node* next) {
			next_ = next;
		}

	private:
		T data_;
		Node* next_{nullptr};
	};

	Node* top_{nullptr};
	std::size_t size_{0u};
};

}  // namespace structures

#endif
