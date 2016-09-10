#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures {

/**
 * @brief Implements a stack(data structure), using arrays.
 * @details This data structure works just like a real 'stack', you add elements
 * to the top of the stack (push), and you remove from the top (pop).
 * It follows the 'LIFO' (last in, first out) principle.
 *
 * @tparam T This is the data type of the elements of the stack.
 */
template<typename T>
class ArrayStack {
public:
	ArrayStack();

	ArrayStack(std::size_t max);

	~ArrayStack();

	void push(const T& data); // empilha

	T pop(); // desempilha

	T& top();

	void clear(); // limpa

	std::size_t size(); // tamanho

	std::size_t max_size();

	bool empty(); // vazia

	bool full(); // cheia

private:
	T* contents; /**< The array that'll contain the elements */
	int top_; /**< The position on the array of the top element */
	std::size_t max_size_; /**< Stack maximum size */

	const static auto DEFAULT_SIZE = 10u; /**< Default size of the stack */
};

/**
 * @brief Default constructor
 * @details Constructs the stack with the default size
 *
 * @tparam T Data type of the elements
 */
template<typename T>
ArrayStack<T>::ArrayStack()
{
	contents = new T[DEFAULT_SIZE];
	top_ = -1;
	max_size_ = DEFAULT_SIZE;
}

/**
 * @brief Constructor with a given maximum size of the stack
 * @details Constructs the stack with 'max' size
 *
 * @param max Maximum size of the stack
 * @tparam T Data type of the elements
 */
template<typename T>
ArrayStack<T>::ArrayStack(std::size_t max)
{
	contents = new T[max];
	top_ = -1;
	max_size_ = max;
}

/**
 * @brief Destructor
 * @details Deletes the 'contents' array
 *
 * @tparam T Data type of the elements
 */
template<typename T>
ArrayStack<T>::~ArrayStack()
{
	delete[] contents;
}

/**
 * @brief Adds 'data' to the top of the stack
 * @details Checks if the stack is not full, then puts 'data' at the top of the
 * stack. Throws std::out_of_range if the stack is full
 *
 * @param data The element that'll be added to the stack
 * @tparam T Data type of the elements
 */
template<typename T>
void ArrayStack<T>::push(const T& data)
{
	if (full()) {
		throw std::out_of_range("Stack is full");
	} else {
		contents[++top_] = data;
	}
}

/**
 * @brief Removes the element at the top of the stack
 * @details Checks if the stack is not empty, then returns and removes the top
 * element of the stack. Throws std::out_of_range if the stack is empty
 *
 * @tparam T Data type of the elements
 * @return The element that was removed
 */
template<typename T>
T ArrayStack<T>::pop()
{
	if (empty()) {
		throw std::out_of_range("Stack is empty");
	} else {
		return contents[top_--];
	}
}

/**
 * @brief Returns a reference to the top element of the stack
 * @details Checks if stack is not empty, then returns the element at the top
 * of the stack. Throws std::out_of_range if the stack is empty
 *
 * @tparam T Data type of the elements
 * @return A reference to the top element of the stack
 */
template<typename T>
T& ArrayStack<T>::top()
{
	if (empty()) {
		throw std::out_of_range("Stack is empty");
	} else {
		return contents[top_];
	}
}

/**
 * @brief Clears the stack
 *
 * @tparam T Data type of the elements
 */
template<typename T>
void ArrayStack<T>::clear()
{
	top_ = -1;
}

/**
 * @brief Returns the number of elements on the stack
 *
 * @tparam T Data type of the elements
 */
template<typename T>
std::size_t ArrayStack<T>::size()
{
	return top_ + 1;
}

/**
 * @brief Returns the maximum size of the stack
 *
 * @tparam T Data type of the elements
 */
template<typename T>
std::size_t ArrayStack<T>::max_size()
{
	return max_size_;
}

/**
 * @brief Checks if stack is empty
 *
 * @tparam T Data type of the elements
 * @return True if stack is empty
 */
template<typename T>
bool ArrayStack<T>::empty()
{
	return top_ == -1;
}

/**
 * @brief Checks if stack is full
 *
 * @tparam T Data type of the elements
 * @return True if stack is full
 */
template<typename T>
bool ArrayStack<T>::full()
{
	return top_ == max_size_ - 1;
}

}

#endif
