#ifndef HEAP_H
#define HEAP_H

#include <vector>

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
class Heap {

public:

	Heap() = default;

	/**
	 * @brief Inserts an element into the Heap
	 */
	void push(const T& data) {
		v.push_back(data);

		auto i = v.size() - 1;

		while(comp(v[(i-1)/2], v[i]) && i > 0) {
			std::swap(v[i], v[(i-1)/2]);
			i = (i-1)/2;
		}
	}

	/**
	 * @brief Removes the top, i.e. the larger, element of the Heap
	 *
	 * @return The removed element
	 */
	T pop() {
		std::swap(v[0], v[v.size() - 1]);
		auto out = v[v.size() - 1];
		v.pop_back();

		heapify(0);

		return out;
	}

	/**
	 * @brief const ref to the top element of the Heap
	 */
	const T& top() const {
		return v[0];
	}

	std::size_t size() const {
		return v.size();
	}

	bool empty() const {
		return v.empty();
	}

private:

	void heapify(std::size_t i) {
		auto left_node  = 2*i + 1;
		auto right_node = 2*i + 2;

		std::size_t larger;

		if (left_node < v.size() && right_node >= v.size()) {
			larger = left_node;
		} else if (right_node < v.size() && left_node >= v.size()) {
			larger = right_node;
		} else {
			larger = comp(v[right_node], v[left_node]) ? left_node : right_node;
		}

		if (larger < v.size() && comp(v[i], v[larger])) {
			std::swap(v[i], v[larger]);
			heapify(larger);
		}
	}

	std::vector<T> v;
	Comparator comp;

};

}

#endif
