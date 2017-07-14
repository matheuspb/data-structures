#ifndef HEAP_H
#define HEAP_H

#include <array_list.h>

namespace structures {

/**
 * @brief A priority queue implementation
 *
 * @details This structure provides constant time lookup to the larger element
 * in the structure, at the cost of logarithmic isertion and removal. The
 * implementation is based on a 'heap' structure, it is basically a binary
 * tree, that each node is larger than its children. The tree is represented
 * using an std::vector, and the children of a node in position `i` are at
 * position `2*i + 1` and `2*i + 2`. You may use another type(e.g.
 * std::greater) in the second template paramater, to get the smaller item at
 * the top.
 *
 * @tparam          T Data type of the elements
 * @tparam Comparator Type providing a strict weak ordering function
 */
template <typename T, typename Comparator = std::less<T>>
class Heap : public PriorityQueue<T> {
public:
	Heap() = default;

	/**
	 * @brief Inserts an element into the Heap
	 */
	void push(const T& data) {
		list.push_back(data);

		auto i = list.size() - 1;

		while (i > 0 && comp(list[(i - 1) / 2], list[i])) {
			std::swap(list[i], list[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

	/**
	 * @brief Removes the top, i.e. the larger, element of the Heap
	 *
	 * @return The removed element
	 */
	T pop() {
		std::swap(list[0], list[list.size() - 1]);
		auto out = list[list.size() - 1];
		list.pop_back();

		heapify(0);

		return out;
	}

	/**
	 * @brief const ref to the top element of the Heap
	 */
	const T& top() const { return list[0]; }

	std::size_t size() const { return list.size(); }

private:
	void heapify(std::size_t i) {
		auto left_node = 2 * i + 1;
		auto right_node = 2 * i + 2;

		std::size_t larger;

		if (left_node < list.size() && right_node >= list.size()) {
			larger = left_node;
		} else if (right_node < list.size() && left_node >= list.size()) {
			larger = right_node;
		} else if (left_node < list.size() && right_node < list.size()) {
			larger = comp(list[right_node], list[left_node]) ? left_node :
															   right_node;
		} else {
			return;
		}

		if (comp(list[i], list[larger])) {
			std::swap(list[i], list[larger]);
			heapify(larger);
		}
	}

	ArrayList<T> list;
	Comparator comp;
};
}

#endif
