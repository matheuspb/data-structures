#ifndef TESTS_H
#define TESTS_H

#include <abstract.h>
#include <assert.h>
#include <initializer_list>
#include <type_traits>
#include <vector>

#define SIZE 10000

namespace tests {

template <typename S>
void test_stack() {
	S stack, copy;

	for (int i = 0; i < SIZE; i++) {
		stack.push(i);
	}

	assert(stack.size() == SIZE);
	assert(stack.top() == SIZE - 1);

	copy = stack;

	stack.clear();

	assert(stack.size() == 0);

	for (int i = 0; i < SIZE; i++) {
		stack.push(i);
	}

	for (int i = SIZE - 1; i >= 0; i--) {
		assert(stack.pop() == i);
		assert(copy.pop() == i);
	}

	// test for memory leaks
	for (int i = 0; i < SIZE; i++) {
		stack.push(i);
	}

	copy = std::move(stack);
}

template <typename Q>
void test_queue() {
	Q queue, copy;

	for (int i = 0; i < SIZE; i++) {
		queue.enqueue(i);
	}

	assert(queue.size() == SIZE);
	assert(queue.front() == 0);
	assert(queue.back() == SIZE - 1);

	copy = queue;

	queue.clear();

	assert(queue.size() == 0);

	for (int i = 0; i < SIZE; i++) {
		queue.enqueue(i);
	}

	for (int i = 0; i < SIZE; i++) {
		assert(queue.dequeue() == i);
		assert(copy.dequeue() == i);
	}

	// test for memory leaks
	for (int i = 0; i < SIZE; i++) {
		queue.enqueue(i);
	}

	copy = std::move(queue);
}

template <typename L>
void test_list() {
	L list, other;

	for (int i = 0; i < SIZE - 1; i++) {
		list.push_front(i);
		assert(list.contains(i));
		assert(list.find(i) == 0);
	}

	other = list;

	list.insert(SIZE, SIZE / 2);
	assert(list.at(SIZE / 2) == SIZE);
	assert(list.size() == SIZE);
	assert(list.erase(SIZE / 2) == SIZE);

	for (int i = 0; i < SIZE - 1; i++) {
		assert(other.contains(i));
		assert(list.pop_back() == i);
		assert(!list.contains(i));
		assert(list.find(i) == list.size());
	}

	assert(list.size() == 0);

	for (int i = 0; i < SIZE; i++) {
		list.push_back(i);
		assert(list.contains(i));
		assert(list.find(i) == (unsigned) i);
	}

	assert(list.size() == SIZE);

	other = std::move(list);

	for (int i = 0; i < SIZE; i++) {
		assert(other.at(other.find(i)) == i);
	}

	for (int i = 0; i < SIZE; i++) {
		assert(other.pop_front() == i);
		assert(!other.contains(i));
		assert(other.find(i) == other.size());
	}

	assert(other.size() == 0);

	for (int i = 0; i < SIZE; i++) {
		other.push_back(i);
	}

	other.clear();
	assert(other.size() == 0);

	// test for memory leaks
	for (int i = 0; i < SIZE; i++) {
		other.push_back(i);
	}
}

template <typename S>
void test_set() {
	S set, other;

	for (double i = 0; i < SIZE; i++) {
		assert(set.insert(i));
		assert(!set.insert(i));
		assert(set.contains(i));
	}

	assert(set.size() == SIZE);

	other = set;

	for (double i = 0; i < SIZE; i++) {
		assert(set.remove(i));
		assert(!set.remove(i));
		assert(!set.contains(i));
		assert(other.contains(i));
	}

	for (double i = 0; i < SIZE; i++) {
		assert(set.insert(i));
	}

	other = std::move(set);

	auto items = other.items();
	other.clear();
	assert(other.size() == 0);

	for (double i = 0; i < SIZE; i++) {
		assert(items.contains(i));
		assert(!other.contains(i));
	}

	// test for memory leaks
	for (double i = 0; i < SIZE; i++) {
		assert(other.insert(i));
	}
}

template <typename Q>
void test_prio_queue() {
	Q pq, copy;

	std::vector<int> v = {4, 5, 3, 2, 8, 9, 1, 7, 6};

	for (int i : v) {
		pq.push(i);
	}

	assert(pq.size() == 9);
	assert(pq.top() == 9);

	copy = pq;

	pq.clear();

	for (int i = 9; i >= 1; i--) {
		assert(copy.pop() == i);
	}

	// test for memory leaks
	for (int i : v) {
		pq.push(i);
	}

	copy = std::move(pq);
}

template <
	typename T,
	typename std::enable_if<
		std::is_base_of<structures::Stack<int>, T>::value, int>::type = 0>
void test_structure() {
	test_stack<T>();
}

template <
	typename T,
	typename std::enable_if<
		std::is_base_of<structures::Queue<int>, T>::value, int>::type = 0>
void test_structure() {
	test_queue<T>();
}

template <
	typename T,
	typename std::enable_if<
		std::is_base_of<structures::List<int>, T>::value &&
			!std::is_base_of<structures::Stack<int>, T>::value &&
			!std::is_base_of<structures::Queue<int>, T>::value,
		int>::type = 0>
void test_structure() {
	test_list<T>();
}

template <
	typename T,
	typename std::enable_if<
		std::is_base_of<structures::Set<double>, T>::value, int>::type = 0>
void test_structure() {
	test_set<T>();
}

template <
	typename T,
	typename std::enable_if<
		std::is_base_of<structures::PriorityQueue<int>, T>::value, int>::type =
		0>
void test_structure() {
	test_prio_queue<T>();
}

}  // namespace tests

#endif
