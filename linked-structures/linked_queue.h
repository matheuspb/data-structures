// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
 * @brief Implements a Queue(data structure).
 * @details This data structure works like a real 'queue', you add(enqueue)
 * elements to the end(tail) of the queue, and remove(dequeue) from the
 * beginning(head). It follows the FIFO(first in, first out) principle.
 *
 * @tparam T This is the data type of the elements of the queue.
 */
template<typename T>
class LinkedQueue {
public:
	/**
	 * @brief Default constructor
	 */
	LinkedQueue() = default;

	/**
	 * @brief Destructor
	 */
	~LinkedQueue() {
		clear();
	}

	/**
	 * @brief Clears the queue
	 */
	void clear() {
		while (!empty()) {
			dequeue();
		}
	}

	/**
	 * @brief Adds 'data' to the end of the queue
	 *
	 * @param data The element that'll be added to the queue
	 */
	void enqueue(const T& data) {
		auto newNode = new Node(data);
		if (empty()) {
			head = newNode;
			tail = newNode;
		} else {
			tail->next(newNode);
			tail = tail->next();
		}
		++size_;
	}

	/**
	 * @brief Removes the element at the beginning of the queue
	 * @details Checks if the queue is not empty, then returns and removes the first
	 * element of the queue. Throws std::out_of_range if the queue is empty
	 *
	 * @return The element that was removed
	 */
	T dequeue() {
		if (empty())
			throw std::out_of_range("Queue is empty");

		auto toDelete = head;
		head = head->next();
		auto out = toDelete->data();
		delete toDelete;
		--size_;
		return out;
	}

	/**
	 * @brief Returns the first element of the queue
	 * @details Checks if the queue is not empty, then returns the first element
	 * on it. Throws std::out_of_range if the queue is empty.
	 *
	 * @return A reference to the first element.
	 */
	T& front() const {
		if (empty())
			throw std::out_of_range("Queue is empty");
		return head->data();
	}

	/**
	 * @brief Returns the last element of the queue
	 * @details Checks if the queue is not empty, then returns the last element
	 * on it. Throws std::out_of_range if the queue is empty.
	 *
	 * @return A reference to the last element.
	 */
	T& back() const {
		if (empty())
			throw std::out_of_range("Queue is empty");
		return tail->data();
	}

	/**
	 * @brief Checks if the queue is empty
	 *
	 * @return True if queue is empty
	 */
	bool empty() const {
		return size_ == 0;
	}

	/**
	 * @brief Returns the number of elements on the queue.
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

	Node* head{nullptr};
	Node* tail{nullptr};
	std::size_t size_{0u};
};

}  // namespace structures

#endif

