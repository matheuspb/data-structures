#include "array_stack.h"

template<typename T>
structures::ArrayStack<T>::ArrayStack()
{
	contents = new T[DEFAULT_SIZE];
	top_ = -1;
	max_size_ = DEFAULT_SIZE;
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max)
{
	contents = new T[max];
	top_ = -1;
	max_size_ = max;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack()
{
	delete[] contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data)
{
	if (full()) {
		throw std::out_of_range("Stack is full");
	} else {
		contents[++top_] = data;
	}
}

template<typename T>
T structures::ArrayStack<T>::pop()
{
	if (empty()) {
		throw std::out_of_range("Stack is empty");
	} else {
		return contents[top_--];
	}
}

template<typename T>
T& structures::ArrayStack<T>::top()
{
	if (empty()) {
		throw std::out_of_range("Stack is empty");
	} else {
		return contents[top_];
	}
}

template<typename T>
void structures::ArrayStack<T>::clear()
{
	top_ = -1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::size()
{
	return top_ + 1;
}

template<typename T>
std::size_t structures::ArrayStack<T>::max_size()
{
	return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty()
{
	return top_ == -1;
}

template<typename T>
bool structures::ArrayStack<T>::full()
{
	return top_ == max_size_ - 1;
}
