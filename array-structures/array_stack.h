#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
@brief Implements a stack(data structure), using arrays.
@details This data structure works just like a real 'stack', you add elements
to the top of the stack (push), and you remove from the top (pop).
It follows the 'LIFO' (last in, first out) principle.

@tparam T Data type of the elements
*/
template<typename T>
class ArrayStack {
public:
	/**
	@brief Default constructor
	*/
	ArrayStack() = default;

	/**
	@brief Constructor with a given maximum size of the stack
	@details Constructs the stack with 'max' size

	@param max Maximum size of the stack
	*/
	explicit ArrayStack(std::size_t max):
		contents{new T[max]},
		max_size_{max} {}

	/**
	@brief Destructor
	@details Deletes the 'contents' array
	*/
	~ArrayStack() {
		delete[] contents;
	}

	/**
	@brief Adds 'data' to the top of the stack
	@details Checks if the stack is not full, then puts 'data' at the top of the
	stack. Throws std::out_of_range if the stack is full

	@param data The element that'll be added to the stack
	*/
	void push(const T& data) {
		if (full()) {
			throw std::out_of_range("Stack is full");
		} else {
			contents[++top_] = data;
		}
	}

	/**
	@brief Removes the element at the top of the stack
	@details Checks if the stack is not empty, then returns and removes the top
	element of the stack. Throws std::out_of_range if the stack is empty

	@return The element that was removed
	*/
	T pop() {
		if (empty()) {
			throw std::out_of_range("Stack is empty");
		} else {
			return contents[top_--];
		}
	}

	/**
	@brief Returns a reference to the top element of the stack
	@details Checks if stack is not empty, then returns the element at the top
	of the stack. Throws std::out_of_range if the stack is empty

	@return A reference to the top element of the stack
	*/
	T& top() const {
		if (empty()) {
			throw std::out_of_range("Stack is empty");
		} else {
			return contents[top_];
		}
	}

	/**
	@brief Clears the stack
	*/
	void clear() {
		top_ = -1;
	}

	/**
	@brief Returns the number of elements on the stack
	*/
	std::size_t size() const {
		return top_ + 1;
	}

	/**
	@brief Returns the maximum size of the stack
	*/
	std::size_t max_size() const {
		return max_size_;
	}

	/**
	@brief Checks if stack is empty

	@return True if stack is empty
	*/
	bool empty() const {
		return top_ == -1;
	}

	/**
	@brief Checks if stack is full

	@return True if stack is full
	*/
	bool full() const {
		return top_ == max_size_ - 1;
	}

private:
	T* contents{new T[DEFAULT_SIZE]};
	int top_{-1};
	std::size_t max_size_{DEFAULT_SIZE};

	const static auto DEFAULT_SIZE{10u};
};

}  // namespace structures

#endif
