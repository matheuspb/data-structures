// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <stdexcept>

namespace structures {

/**
 * @brief Implements a doubly linked list.
 * @details A doubly linked list, is a linked list where each node points to
 * both, the next and the previous node.
 *
 * @tparam T Data type of the elements.
 */
template<typename T>
class DoublyLinkedList {
public:
	/**
	 * @brief Default constructor
	 */
	DoublyLinkedList() = default;

	/**
	 * @brief Destructor
	 */
	~DoublyLinkedList() {
		clear();
	}

	/**
	 * @brief Clears all the elements on the list
	 */
	void clear() {
		while (!empty()) {
			pop_front();
		}
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
		head = new Node(data, head);
		if (head->next() != nullptr)
			head->next()->prev(head);
		++size_;
	}

	/**
	 * @brief Inserts at a given position of the list
	 *
	 * @param data The element that'll be inserted
	 * @param index The position where 'data' will be inserted
	 */
	void insert(const T& data, std::size_t index) {
		if (index == 0) return push_front(data);
		if (index > size_) throw std::out_of_range("Invalid index");
		Node* it = head;
		for (std::size_t i = 0; i < index - 1; ++i) {
			it = it->next();
		}
		Node* newNode = new Node(data, it, it->next());
		if (it->next() != nullptr)
			it->next()->prev(newNode);
		it->next(newNode);
		++size_;
	}

	/**
	 * @brief Inserts the element sorted into the list
	 *
	 * @param data The element that'll be inserted
	 */
	void insert_sorted(const T& data) {
		if (empty() || data <= head->data())
			return push_front(data);
		Node* it = head;
		while (it->next() != nullptr && data > it->next()->data()) {
			it = it->next();
		}
		Node* newNode = new Node(data, it, it->next());
		if (it->next() != nullptr)
			it->next()->prev(newNode);
		it->next(newNode);
		++size_;
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
		if (index == 0) return pop_front();
		Node* it = head;
		for (std::size_t i = 0; i < index - 1; ++i) {
			it = it->next();
		}
		Node* toDelete = it->next();
		it->next(toDelete->next());
		if (toDelete->next() != nullptr)
			toDelete->next()->prev(it);
		T out = toDelete->data();
		delete toDelete;
		--size_;
		return out;
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
		if (empty()) throw std::out_of_range("List is empty");
		Node* toDelete = head;
		head = head->next();
		if (head != nullptr)
			head->prev(nullptr);
		T out = toDelete->data();
		delete toDelete;
		--size_;
		return out;
	}

	/**
	 * @brief Removes 'data' from the list, if it exists
	 *
	 * @param data The element that'll be removed
	 */
	void remove(const T& data) {
		if (head->data() == data) {
			pop_front();
			return;
		}
		Node* it;
		for (it = head; it->next()->data() != data; it = it->next()) {
			if (it->next() == nullptr)
				return;  // Reached end of the list
		}
		Node* toDelete = it->next();
		it->next(toDelete->next());
		toDelete->next()->prev(it);
		delete toDelete;
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
		for (Node* it = head; it->next() != nullptr; it = it->next()) {
			if (it->data() == data) return true;
		}
		return false;
	}

	/**
	 * @brief Returns a reference to the element at a given index
	 * @details If index is out of the list's bounds, it throws an
	 * std::out_of_range exception
	 *
	 * @param index The index on the list of the element that'll be returned
	 */
	T& at(std::size_t index) {
		if (index >= size_) throw std::out_of_range("Index out of bounds");
		Node* it = head;
		for (std::size_t i = 0; i < index; ++i) {
			it = it->next();
		}
		return it->data();
	}

	/**
	 * @brief const version of 'at()'
	 */
	const T& at(std::size_t index) const {
		if (index >= size_) throw std::out_of_range("Index out of bounds");
		Node* it = head;
		for (std::size_t i = 0; i < index; ++i) {
			it = it->next();
		}
		return it->data();
	}

	/**
	 * @brief Returns the position of 'data' on the list
	 *
	 * @param data The element that'll be searched
	 */
	std::size_t find(const T& data) const {
		std::size_t index = 0;
		for (Node* it = head; it != nullptr; it = it->next()) {
			if (it->data() == data)
				break;
			++index;
		}
		return index;
	}

	/**
	 * @brief Returns the size of the list
	 */
	std::size_t size() const {
		return size_;
	}

private:
	class Node {
	public:
		explicit Node(const T& data): data_{data} {}
		Node(const T& data, Node* next): data_{data}, next_{next} {}
		Node(const T& data, Node* prev, Node* next):
			data_{data}, prev_{prev}, next_{next} {}

		T& data() {
			return data_;
		}
		const T& data() const {
			return data_;
		}

		Node* prev() {
			return prev_;
		}
		const Node* prev() const {
			return prev_;
		}

		void prev(Node* node) {
			prev_ = node;
		}

		Node* next() {
			return next_;
		}
		const Node* next() const {
			return next_;
		}

		void next(Node* node) {
			next_ = node;
		}

	private:
		T data_;
		Node* prev_{nullptr};
		Node* next_{nullptr};
	};

	Node* head{nullptr};
	std::size_t size_{0u};
};

}  // namespace structures

#endif

