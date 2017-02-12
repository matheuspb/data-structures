#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
@brief Implements a Queue(data structure), using arrrays.
@details This data structure works like a real 'queue', you add(enqueue)
elements to the end of the queue, and remove(dequeue) from the beginning.
It follow the FIFO(first in, first out) principle.

@tparam T Data type of the elements
*/
template<typename T>
class ArrayQueue {
public:
	/**
	@brief Default constructor
	*/
	ArrayQueue() = default;

	/**
	@brief Constructor with a given maximum size of the queue
	@details Constructs the queue with 'max' size

	@param max Maximum size of the queue
	*/
	explicit ArrayQueue(std::size_t max):
		contents{new T[max]},
		max_size_{max} {}

	/**
	@brief Destructor
	@details Deletes the 'contents' array
	*/
	~ArrayQueue() {
		delete[] contents;
	}

	/**
	@brief Adds 'data' to the end of the queue
	@details Checks if the queue is not full, then puts 'data' at the end of the
	queue. Throws std::out_of_range if the queue is full

	@param data The element that'll be added to the queue
	*/
	void enqueue(const T& data) {
		if (full()) {
			throw std::out_of_range("Queue is full");
		} else {
			contents[size_++] = data;
		}
	}

	/**
	@brief Removes the element at the beginning of the queue
	@details Checks if the queue is not empty, then returns and removes the first
	element of the queue. Throws std::out_of_range if the queue is empty

	@return The element that was removed
	*/
	T dequeue() {
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

	/**
	@brief Returns a reference to the last element of the queue
	@details Checks if the queue is not empty, then returns a reference to the
	element at the end of the queue. Throws std::out_of_range if the queue is
	empty

	@return A reference to the alst element of the queue
	*/
	T& back() const {
		if (empty()) {
			throw std::out_of_range("Queue is empty");
		} else {
			return contents[size_-1];
		}
	}

	/**
	@brief Clears the queue
	*/
	void clear() {
		size_ = 0;
	}

	/**
	@brief Returns the number of elements on the queue
	*/
	std::size_t size() const {
		return size_;
	}

	/**
	@brief Returns the maximum size of the queue
	*/
	std::size_t max_size() const {
		return max_size_;
	}

	/**
	@brief Checks if the queue is empty

	@return True if queue is empty
	*/
	bool empty() const {
		return size_ == 0;
	}

	/**
	@brief Checks if queue is full

	@return True if queue is full
	*/
	bool full() const {
		return size_ == max_size_;
	}

private:
	T* contents{new T[DEFAULT_SIZE]};
	std::size_t size_{0u};
	std::size_t max_size_{DEFAULT_SIZE};

	const static auto DEFAULT_SIZE{10u};
};

}  // namespace structures

#endif
