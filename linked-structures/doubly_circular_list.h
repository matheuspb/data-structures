// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <stdexcept>

namespace structures {

/**
* @brief Implementation of a doubly linked list
* @tparam T Data type of the elements
*/
template<typename T>
class DoublyCircularList {
public:
	/**
	* @brief Default constructor
	*/
	DoublyCircularList() = default;

	/**
	* @brief Destructor
	*/
	~DoublyCircularList() {
		clear();
	}

	/**
	* @brief Clears all the elements on the list
	*/
	void clear() {
		while(!empty()) {
			pop_back();
		}
	}

	/**
	* @brief Inserts at the end of the list
	* @param data The element that'll be inserted
	*/
	void push_back(const T& data) {
		if (empty()) {
			head = new Node(data);
			head->next(head);
			head->prev(head);
		} else {
			auto newNode = new Node(data, head->prev(), head);
			newNode->prev()->next(newNode);
			head->prev(newNode);
		}
		++size_;
	}

	/**
	* @brief Inserts at the beginning of the list
	* @param data The element that'll be inserted
	*/
	void push_front(const T& data) {
		push_back(data);
		head = head->prev();
	}

	/**
	* @brief Inserts at a given position of the list
	* @param data The element that'll be inserted
	* @param index The position where 'data' will be inserted
	*/
	void insert(const T& data, std::size_t index) {
		if (index == 0) {
			return push_back(data);
		} else if (index > size_) {
			throw std::out_of_range("Invalid index (insert())");
		} else {
			auto it = head;
			for (std::size_t i = 0; i < index - 1; ++i) {
				it = it->next();
			}
			it->next(new Node(data, it, it->next()));
			it->next()->next()->prev(it->next());
			++size_;
		}
	}

	/**
	* @brief Inserts the element sorted into the list
	* @param data The element that'll be inserted
	*/
	void insert_sorted(const T& data) {
		if (empty() || data <= head->data())
			return push_front(data);
		auto it = head;
		while (it->next() != head && data > it->next()->data()) {
			it = it->next();
		}
		auto newNode = new Node(data, it, it->next());
		it->next()->prev(newNode);
		it->next(newNode);
		++size_;
	}

	/**
	* @brief Removes the element at the given index
	* @param index The index of the element that'll be removed
	* @return The element that was removed
	*/
	T pop(std::size_t index) {
		if (index >= size_) throw std::out_of_range(
				"Index out of bounds (pop())");
		auto oldHead = head;
		for (std::size_t i = 0; i < index + 1; ++i) {
			head = head->next();
		}
		auto out = pop_back();
		head = oldHead;
		return out;
	}

	/**
	* @brief Removes the element at the end of the list
	* @return The removed element
	*/
	T pop_back() {
		if (empty()) throw std::out_of_range("List is empty (pop_back())");
		auto toDelete = head->prev();
		head->prev(toDelete->prev());
		toDelete->prev()->next(head);
		T out = toDelete->data();
		delete toDelete;
		--size_;
		return out;
	}

	/**
	* @brief Removes the element at the beginning of the list
	* @return The removed element
	*/
	T pop_front() {
		if (empty()) throw std::out_of_range("List is empty (pop_front())");
		head = head->next();
		return pop_back();
	}

	/**
	* @brief Removes 'data' from the list, if it exists
	* @param data The element that'll be removed
	*/
	void remove(const T& data) {
		auto it = head->next();
		for (; it->data() != data; it = it->next()) {
			if (it == head)
				return;  // Reached end of the list
		}
		auto oldHead = head;
		head = it->next();
		pop_back();
		head = oldHead;
	}

	/**
	* @brief Checks if the list is empty
	* @return True if the list is empty
	*/
	bool empty() const {
		return size_ == 0;
	}

	/**
	* @brief Checks if the list contains an element(data)
	* @param data The element that'll be checked if it is contained by the list
	* @return True if the list contains 'data'
	*/
	bool contains(const T& data) const {
		for (auto it = head; it->next() != head; it = it->next()) {
			if (it->data() == data) return true;
		}
		return false;
	}

	/**
	* @brief Returns a reference to the element at a given index
	* @details If index is out of the list's bounds, it throws an
	* std::out_of_range exception
	* @param index The index on the list of the element that'll be returned
	*/
	T& at(std::size_t index) {
		if (index >= size_) throw std::out_of_range("Index out of bounds");
		auto it = head;
		for (std::size_t i = 0; i < index; ++i) {
			it = it->next();
		}
		return it->data();
	}

	/**
	* @brief Returns the position of 'data' on the list
	* @param data The element that'll be searched
	*/
	std::size_t find(const T& data) const {
		std::size_t index = 1;
		if (head->data() == data)
			return 0;

		for (auto it = head->next(); it != head; it = it->next()) {
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

		Node* prev() const {
			return prev_;
		}

		void prev(Node* node) {
			prev_ = node;
		}

		Node* next() const {
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

