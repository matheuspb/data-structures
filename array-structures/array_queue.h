#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>
#include <stdexcept>

#include "array_list.h"

namespace structures {

/**
 * @brief Implements a Queue(data structure), using arrrays.
 * @details This data structure works like a real 'queue', you add(enqueue)
 * elements to the end of the queue, and remove(dequeue) from the beginning.
 * It follow the FIFO(first in, first out) principle.
 *
 * @tparam T Data type of the elements
 */
template<typename T>
class ArrayQueue : private ArrayList<T> {

public:

	using ArrayList<T>::clear;
	using ArrayList<T>::size;
	using ArrayList<T>::max_size;
	using ArrayList<T>::empty;
	using ArrayList<T>::full;

	ArrayQueue(): ArrayList<T>{} {}

	/**
	 * @brief Constructor with a given maximum size of the queue
	 *
	 * @param max Maximum size of the queue
	 */
	explicit ArrayQueue(std::size_t max): ArrayList<T>{max} {}

	/**
	 * @brief Adds 'data' to the end of the queue

	 * @param data The element that'll be added to the queue
	 */
	void enqueue(const T& data) {
		if (full()) {
			throw std::out_of_range("Queue is full");
		} else {
			ArrayList<T>::push_back(data);
		}
	}

	/**
	 * @brief Removes the element at the beginning of the queue
	 *
	 * @return The element that was removed
	 */
	T dequeue() {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		} else {
			return ArrayList<T>::pop_front();
		}
	}

	/**
	 * @brief Returns a reference to the last element of the queue
	 *
	 * @return A reference to the last element of the queue
	 */
	const T& back() const {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		} else {
			return this->at(this->size() - 1);
		}
	}

};

}  // namespace structures

#endif
