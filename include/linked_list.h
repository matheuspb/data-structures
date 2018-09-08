#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

#include <traits.h>

namespace structures {

/**
 * @brief Implements a singly linked list
 * @details A linked list, is a list where each node has a pointer to the next
 * node, so, you only need a pointer to the first node (which here is head).
 * The last node points to 'nullptr'.
 *
 * @tparam T Data type of the elements
 */
template <typename T>
class LinkedList {
public:
	LinkedList() = default;

	LinkedList(const LinkedList<T>& other)
		: head{copy_list(other.head)}, size_{other.size_} {}

	LinkedList(LinkedList<T>&& other) : head{other.head}, size_{other.size_} {
		other.head = nullptr;
		other.size_ = 0;
	}

	LinkedList<T>& operator=(const LinkedList<T>& other) {
		LinkedList<T> copy{other};
		std::swap(head, copy.head);
		std::swap(size_, copy.size_);
		return *this;
	}

	LinkedList<T>& operator=(LinkedList<T>&& other) {
		LinkedList<T> copy{std::move(other)};
		std::swap(head, copy.head);
		std::swap(size_, copy.size_);
		return *this;
	}

	virtual ~LinkedList() { clear(); }

	/**
	 * @brief Clears the list
	 */
	void clear() {
		while (!empty())
			pop_front();
	}

	/**
	 * @brief Inserts at the end of the list
	 *
	 * @param data The element that'll be inserted
	 */
	void push_back(const T& data) { insert(data, size_); }

	/**
	 * @brief Inserts at the beginning of the list
	 *
	 * @param data The element that'll be inserted
	 */
	void push_front(const T& data) {
		head = new Node(data, head);
		++size_;
	}

	/**
	 * @brief Inserts at a given position of the list
	 *
	 * @param data The element that'll be inserted
	 * @param index The position where 'data' will be inserted
	 */
	void insert(const T& data, std::size_t index) {
		if (index == 0) {
			return push_front(data);
		} else if (index > size_) {
			throw std::out_of_range("Invalid index");
		} else {
			Node* it = head;
			for (std::size_t i = 0; i < index - 1; ++i) {
				it = it->next;
			}
			it->next = new Node(data, it->next);

			++size_;
		}
	}

	/**
	 * @brief Inserts the element sorted into the list
	 *
	 * @param data The element that'll be inserted
	 */
	void insert_sorted(const T& data) {
		if (empty() || data <= head->data) {
			return push_front(data);
		} else {
			Node* it = head;
			while (it->next != nullptr && data > it->next->data) {
				it = it->next;
			}
			it->next = new Node(data, it->next);

			++size_;
		}
	}

	/**
	 * @brief Checks if the index is valid, then returns a reference to the
	 * element at the given index of the list
	 * @param index The index on the list of the element that'll be returned
	 *
	 * @return A reference to the element at the given index
	 */
	T& at(std::size_t index) {
		return const_cast<T&>(static_cast<const LinkedList*>(this)->at(index));
	}

	const T& at(std::size_t index) const {
		if (index >= size_) {
			throw std::out_of_range("Index out of bounds");
		} else {
			Node* it = head;
			for (std::size_t i = 0; i < index; i++) {
				it = it->next;
			}
			return it->data;
		}
	}

	/**
	 * @brief Removes the element at the given index
	 *
	 * @param index The index of the element that'll be removed
	 *
	 * @return The element that was removed
	 */
	T erase(std::size_t index) {
		if (index >= size_) {
			throw std::out_of_range("Index out of bounds");
		} else if (index == 0) {
			return pop_front();
		} else {
			Node* it = head;
			for (std::size_t i = 0; i < index - 1; ++i) {
				it = it->next;
			}

			T removed = it->next->data;
			Node* p_removed = it->next;
			it->next = it->next->next;

			--size_;
			delete p_removed;
			return removed;
		}
	}

	/**
	 * @brief Removes the element at the end of the list
	 *
	 * @return The removed element
	 */
	T pop_back() { return erase(size_ - 1); }

	/**
	 * @brief Removes the element at the beginning of the list
	 *
	 * @return The removed element
	 */
	T pop_front() {
		if (empty()) {
			throw std::out_of_range("List is empty");
		} else {
			T removed = head->data;
			Node* old_head = head;
			head = head->next;
			delete old_head;
			--size_;
			return removed;
		}
	}

	/**
	 * @brief Removes 'data' from the list
	 *
	 * @param data The element that'll be removed
	 */
	void remove(const T& data) {
		if (head->data == data) {
			pop_front();
			return;
		} else {
			Node* it;
			for (it = head; it->next->data != data; it = it->next) {
				if (it->next == nullptr)
					return;
			}

			Node* p_removed = it->next;
			it->next = it->next->next;
			delete p_removed;

			--size_;
		}
	}

	/**
	 * @brief Checks if the list is empty
	 *
	 * @return True if the list is empty
	 */
	bool empty() const { return size_ == 0; }

	/**
	 * @brief Checks if the list contains an element(data)
	 *
	 * @param data The element that'll be checked if it is contained by the
	 * list
	 *
	 * @return True if the list contains 'data'
	 */
	bool contains(const T& data) const { return find(data) != size_; }

	/**
	 * @brief Returns the position of 'data' on the list
	 *
	 * @param data The element that'll be searched
	 *
	 * @return The index of 'data' on the list
	 */
	std::size_t find(const T& data) const {
		std::size_t index = 0;
		for (Node* it = head; it != nullptr; it = it->next) {
			if (it->data == data)
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
	std::size_t size() const { return size_; }

	T& front() { return head->data; }

	const T& front() const { return head->data; }

	T& back() {
		Node* it = head;
		for (std::size_t i = 1; i < size_; ++i) {
			it = it->next;
		}
		return it->data;
	}

	const T& back() const {
		Node* it = head;
		for (std::size_t i = 1; i < size_; ++i) {
			it = it->next;
		}
		return it->data;
	}

private:
	struct Node {
		explicit Node(const T& data) : data{data} {}
		Node(const T& data, Node* next) : data{data}, next{next} {}

		T data;
		Node* next{nullptr};
	};

	static Node* copy_list(const Node* other_head) {
		auto new_tail = new Node(other_head->data);
		auto new_head = new_tail;
		auto it = other_head->next;

		while (it != nullptr) {
			new_tail->next = new Node(it->data);
			new_tail = new_tail->next;
			it = it->next;
		}

		return new_head;
	}

	Node* head{nullptr};
	std::size_t size_{0u};
};

}  // namespace structures

/* list trait */
template <>
const bool traits::is_list<structures::LinkedList>::value = true;

/* name trait */
template <>
const std::string traits::type<structures::LinkedList>::name = "LinkedList";

#endif
