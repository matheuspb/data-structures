#ifndef STRUCTURES_ABSTRACT_H
#define STRUCTURES_ABSTRACT_H

namespace structures {

template<typename T>
class Stack {

public:
	virtual void push(const T& data) = 0;
	virtual T pop() = 0;
	virtual const T& top() const = 0;
	virtual void clear() = 0;
	virtual std::size_t size() const = 0;

};

template<typename T>
class Queue {

public:
	virtual void enqueue(const T& data) = 0;
	virtual T dequeue() = 0;
	virtual const T& front() const = 0;
	virtual const T& back() const = 0;
	virtual void clear() = 0;
	virtual std::size_t size() const = 0;

};

}

#endif
