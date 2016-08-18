#include "array_queue.h"

template<typename T>
structures::ArrayQueue<T>::ArrayQueue()
{
	contents = new T[DEFAULT_SIZE];
	size_ = -1;
	max_size_ = DEFAULT_SIZE;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max)
{
	contents = new T[max];
	size_ = -1;
	max_size_ = max;
}


template<typename T>
structures::ArrayQueue<T>::~ArrayQueue()
{
	delete[] contents;
}


template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data)
{
	if (full()) {
		throw std::out_of_range("Queue is full");
	} else {
		contents[++size_] = data;
	}
}

template<typename T>
T structures::ArrayQueue<T>::dequeue()
{
	if (empty()) {
		throw std::out_of_range("Queue is empty");
	} else {
		T first = contents[0];
		for (int i = 1; i < size(); ++i) {
			contents[i-1] = contents[i];
		}
		size_--;
		return first;
	}
}

template<typename T>
T& structures::ArrayQueue<T>::back()
{
	if (empty()) {
		throw std::out_of_range("Queue is empty");
	} else {
		return contents[size_];
	}
}

template<typename T>
void structures::ArrayQueue<T>::clear()
{
	size_ = -1;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size()
{
	return size_ + 1;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size()
{
	return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty()
{
	return size_ == -1;
}

template<typename T>
bool structures::ArrayQueue<T>::full()
{
	return size_ + 1 == max_size_;
}
