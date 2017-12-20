#ifndef STRUCTURES_QUEUE_H
#define STRUCTURES_QUEUE_H

#include <cstdint>

#include <doubly_circular_list.h>

namespace structures {

template <typename T, typename Container = DoublyCircularList<T>>
class Queue {
public:
	void push(const T& data) { return cont.push_back(data); }
	T pop() { return cont.pop_front(); }
	T& front() { return cont.front(); }
	const T& front() const { return cont.front(); }
	T& back() { return cont.back(); }
	const T& back() const { return cont.back(); }
	void clear() { return cont.clear(); }
	std::size_t size() const { return cont.size(); }

private:
	Container cont;
};

}  // namespace structures

#endif
