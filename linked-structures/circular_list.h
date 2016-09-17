// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
 * @brief Implements a circular linked list
 * @details This is an implementation of a circular linked list. Here, head
 * always points to a 'sentinel' node, so the list is never empty, and the last
 * node always points to 'head' (sentinel).
 *
 * @tparam T Data type of the elements
 */
template<typename T>
class CircularList {
public:
	/**
	 * @brief Default constructor
	 */
	CircularList() {
		auto sentinel = new Node(0);
		sentinel->next(sentinel);
		head = sentinel;
	}

	/**
	 * @brief Destructor
	 */
	~CircularList() {
		clear();
		delete head;
	}

	/**
	 * @brief Clears the list
	 */
	void clear() {
		while(!empty())
			pop_front();
	}

	/**
	 * @brief Inserts at the end of the list
	 *
	 * @param data The element that'll be inserted
	 */
	void push_back(const T& data) {
		insert(data, size_);
	}

	/**
	 * @brief Inserts at the beginning of the list
	 *
	 * @param data The element that'll be inserted
	 */
	void push_front(const T& data) {
		insert(data, 0);
	}

	/**
	 * @brief Inserts at a given position of the list
	 *
	 * @param data The element that'll be inserted
	 * @param index The position where 'data' will be inserted
	 */
	void insert(const T& data, std::size_t index) {
		if (index > size_) throw std::out_of_range("Invalid index");
		Node* it = head;
		for (std::size_t i = 0; i < index; ++i) {
			it = it->next();
		}
		it->next(new Node(data, it->next()));
		++size_;
	}

	/**
	 * @brief Inserts the element sorted into the list
	 *
	 * @param data The element that'll be inserted
	 */
	void insert_sorted(const T& data) {
		if (empty() || data <= head->next()->data())
			return insert(data, 0);
		Node* it = head->next();
		while (it->next() != head && data > it->next()->data()) {
			it = it->next();
		}
		it->next(new Node(data, it->next()));
		++size_;
	}

	/**
	 * @brief Checks if the index is valid, then returns a reference to the
	 * element at the given index of the list
	 *
	 * @param index The index on the list of the element that'll be returned
	 *
	 * @return A reference to the element at the given index
	 */
	T& at(std::size_t index) {
		if (index >= size_) throw std::out_of_range("Index out of bounds");
		Node* it = head->next();
		for (std::size_t i = 0; i < index; ++i) {
			it = it->next();
		}
		return it->data();
	}

	/**
	 * @brief Removes the element at the given index
	 *
	 * @param index The index of the element that'll be removed
	 *
	 * @return The element that was removed
	 */
	T pop(std::size_t index) {
		if (index >= size_) throw std::out_of_range("Index out of bounds");
		Node* it = head;
		for (std::size_t i = 0; i < index; ++i) {
			it = it->next();
		}
		T removed = it->next()->data();
		Node* p_removed = it->next();
		it->next(it->next()->next());
		--size_;
		delete p_removed;
		return removed;
	}

	/**
	 * @brief Removes the element at the end of the list
	 *
	 * @return The removed element
	 */
	T pop_back() {
		return pop(size_ - 1);
	}

	/**
	 * @brief Removes the element at the beginning of the list
	 *
	 * @return The removed element
	 */
	T pop_front() {
		return pop(0);
	}

	/**
	 * @brief Removes 'data' from the list
	 *
	 * @param data The element that'll be removed
	 */
	void remove(const T& data) {
		auto it = head;
		for (; it->next()->data() != data; it = it->next()) {
			if (it->next() == head)
				return;
		}
		Node* p_removed = it->next();
		it->next(it->next()->next());
		delete p_removed;
		--size_;
	}

	/**
	 * @brief Checks if the list is empty
	 *
	 * @return True if the list is empty
	 */
	bool empty() const {
		return size_ == 0;
	}

	/**
	 * @brief Checks if the list contains an element(data)
	 *
	 * @param data The element that'll be checked if it is contained by the list
	 *
	 * @return True if the list contains 'data'
	 */
	bool contains(const T& data) const {
		for (auto it = head->next(); it != head; it = it->next()) {
			if (it->data() == data)
				return true;
		}
		return false;
	}

	/**
	 * @brief Returns the position of 'data' on the list
	 *
	 * @param data The element that'll be searched
	 *
	 * @return The index of 'data' on the list
	 */
	std::size_t find(const T& data) const {
		std::size_t index = 0;
		for (auto it = head->next(); it != head; it = it->next()) {
			if (it->data() == data)
				break;
			++index;
		}
		return index;
	}

	/**
	 * @brief Size of the list
	 *
	 * @return Size of the list
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

		Node* next() const {
			return next_;
		}

		void next(Node* node) {
			next_ = node;
		}

	private:
		T data_;
		Node* next_{nullptr};
	};

	Node* head;
	std::size_t size_{0u};
};

}  // namespace structures

#endif
