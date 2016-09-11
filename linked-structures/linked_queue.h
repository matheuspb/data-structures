// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedQueue {
	public:
	LinkedQueue() = default;

	~LinkedQueue() {
		clear();
	}

	void clear() {
		while (!empty()) {
			dequeue();
		}
	}

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

	T& front() const {
		if (empty())
			throw std::out_of_range("Queue is empty");
		return head->data();
	}

	T& back() const {
		if (empty())
			throw std::out_of_range("Queue is empty");
		return tail->data();
	}

	bool empty() const {
		return size_ == 0;
	}

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

