#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
 * @brief Implements a singly linked list
 * @details A linked list, is a list where each node has a pointer to the next
 * node, so, you only need a pointer to the first node (which here is head). The
 * last node points to 'nullptr'.
 *
 * @tparam T Data type of the elements
 */
template<typename T>
class LinkedList {
public:
	LinkedList() = default;
	~LinkedList();
	void clear();
	void push_back(const T& data);
	void push_front(const T& data);
	void insert(const T& data, std::size_t index);
	void insert_sorted(const T& data);
	T& at(std::size_t index);
	T pop(std::size_t index);
	T pop_back();
	T pop_front();
	void remove(const T& data);
	bool empty() const;
	bool contains(const T& data) const;
	std::size_t find(const T& data) const;
	std::size_t size() const;
private:
	class Node {
	public:
		Node(const T& data):
			data_{data}
		{}

		Node(const T& data, Node* next):
			data_{data},
			next_{next}
		{}

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

		void next(Node* node) {
			next_ = node;
		}
	private:
		T data_;
		Node* next_{nullptr};
	};

	Node* end() {
		auto it = head;
		for (auto i = 1u; i < size(); ++i) {
			it = it->next();
		}
		return it;
	}

	Node* head{nullptr};
	std::size_t size_{0u};
};

/**
 * @brief Destructor
 */
template<typename T>
LinkedList<T>::~LinkedList()
{
	while(!empty()) {
		pop_front();
	}
}

/**
 * @brief Clears the list
 */
template<typename T>
void LinkedList<T>::clear()
{
	while(!empty()) {
		pop_front();
	}
}

/**
 * @brief Inserts at the end of the list
 *
 * @param data The element that'll be inserted
 */
template<typename T>
void LinkedList<T>::push_back(const T& data)
{
	insert(data, size_);
}

/**
 * @brief Inserts at the beginning of the list
 *
 * @param data The element that'll be inserted
 */
template<typename T>
void LinkedList<T>::push_front(const T& data)
{
	head = new Node(data, head);
	++size_;
}

/**
 * @brief Inserts at a given position of the list
 *
 * @param data The element that'll be inserted
 * @param index The position where 'data' will be inserted
 */
template<typename T>
void LinkedList<T>::insert(const T& data, std::size_t index)
{
	if (index == 0) return push_front(data);
	if (index > size_) throw std::out_of_range("Invalid index");
	Node* it = head;
	for (std::size_t i = 0; i < index - 1; ++i) {
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
template<typename T>
void LinkedList<T>::insert_sorted(const T& data)
{
	if (empty() || data <= head->data())
		return push_front(data);
	Node* it = head;
	while (it->next() != nullptr && data > it->next()->data()) {
		it = it->next();
	}
	it->next(new Node(data, it->next()));
	++size_;
}

/**
 * @brief Checks if the index is valid, then returns a reference to the element
 * at the given index of the list
 *
 * @param index The index on the list of the element that'll be returned
 *
 * @return A reference to the element at the given index
 */
template<typename T>
T& LinkedList<T>::at(std::size_t index)
{
	if (index >= size_) throw std::out_of_range("Index out of bounds");
	Node* it = head;
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
template<typename T>
T LinkedList<T>::pop(std::size_t index)
{
	if (index >= size_) throw std::out_of_range("Index out of bounds");
	if (index == 0) return pop_front();
	Node* it = head;
	for (std::size_t i = 0; i < index - 1; ++i) {
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
template<typename T>
T LinkedList<T>::pop_back()
{
	return pop(size_ - 1);
}

/**
 * @brief Removes the element at the beginning of the list
 *
 * @return The removed element
 */
template<typename T>
T LinkedList<T>::pop_front()
{
	if (empty()) throw std::out_of_range("List is empty");
	T removed = head->data();
	Node* old_head = head;
	head = head->next();
	delete old_head;
	--size_;
	return removed;
}

/**
 * @brief Removes 'data' from the list
 *
 * @param data The element that'll be removed
 */
template<typename T>
void LinkedList<T>::remove(const T& data)
{
	if (head->data() == data) {
		pop_front();
		return;
	}
	Node* it;
	for (it = head; it->next()->data() != data; it = it->next()) {
		if (it->next() == nullptr)
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
template<typename T>
bool LinkedList<T>::empty() const
{
	return size_ == 0;
}

/**
 * @brief Checks if the list contains an element(data)
 *
 * @param data The element that'll be checked if it is contained by the list
 *
 * @return True if the list contains 'data'
 */
template<typename T>
bool LinkedList<T>::contains(const T& data) const
{
	for (Node* it = head; it->next() != nullptr; it = it->next()) {
		if (it->data() == data) return true;
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
template<typename T>
std::size_t LinkedList<T>::find(const T& data) const
{
	std::size_t index = 0;
	for (Node* it = head; it != nullptr; it = it->next()) {
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
template<typename T>
std::size_t LinkedList<T>::size() const
{
	return size_;
}

}

#endif

