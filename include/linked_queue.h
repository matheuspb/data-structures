#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

#include "doubly_circular_list.h"

namespace structures {

/**
 * @brief Implements a Queue(data structure).
 * @details This data structure works like a real 'queue', you add(enqueue)
 * elements to the end(tail) of the queue, and remove(dequeue) from the
 * beginning(head). It follows the FIFO(first in, first out) principle.
 *
 * @tparam T This is the data type of the elements of the queue.
 */
template <typename T>
class LinkedQueue : private DoublyCircularList<T>, public Queue<T> {
public:
	using DoublyCircularList<T>::empty;

	LinkedQueue() : DoublyCircularList<T>{} {}

	/**
	 * @brief Adds 'data' to the end of the queue
	 *
	 * @param data The element that'll be added to the queue
	 */
	void enqueue(const T& data) { DoublyCircularList<T>::push_back(data); }

	/**
	 * @brief Removes the element at the beginning of the queue
	 *
	 * @return The element that was removed
	 */
	T dequeue() {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		} else {
			return DoublyCircularList<T>::pop_front();
		}
	}

	/**
	 * @brief Returns the first element of the queue
	 *
	 * @return A reference to the first element.
	 */
	const T& front() const {
		try {
			return this->at(0);
		} catch (const std::out_of_range& e) {
			throw std::out_of_range("Queue is empty");
		}
	}

	/**
	 * @brief Returns the last element of the queue
	 *
	 * @return A reference to the last element.
	 */
	const T& back() const {
		try {
			return this->at(this->size() - 1);
		} catch (const std::out_of_range& e) {
			throw std::out_of_range("Queue is empty");
		}
	}

	void clear() { DoublyCircularList<T>::clear(); }

	std::size_t size() const { return DoublyCircularList<T>::size(); }
};

}  // namespace structures

#endif
