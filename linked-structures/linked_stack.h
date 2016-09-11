// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedStack {
	public:
	LinkedStack() = default;

	~LinkedStack() {
		clear();
	}

	void clear() {
		while (!empty()) {
			pop();
		}
	}

	void push(const T& data) {
		top_ = new Node(data, top_);
		++size_;
	}

	T pop() {
		if (empty())
			throw std::out_of_range("Stack is empty");

		auto toDelete = top_;
		top_ = top_->next();
		auto out = toDelete->data();
		delete toDelete;
		--size_;
		return out;
	}

	T& top() const {
		if (empty())
			throw std::out_of_range("Stack is empty");
		return top_->data();
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

	Node* top_{nullptr};
	std::size_t size_{0u};
};

}  // namespace structures

#endif
