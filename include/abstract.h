#ifndef STRUCTURES_ABSTRACT_H
#define STRUCTURES_ABSTRACT_H

#include <cstdint>

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

template<typename T>
class List {

public:
	virtual ~List() = 0;
	virtual void clear() = 0;

	virtual void push_front(const T&) = 0;
	virtual void push_back(const T&) = 0;
	virtual void insert(const T&, std::size_t) = 0;

	virtual T pop_front() = 0;
	virtual T pop_back() = 0;
	virtual T erase(std::size_t) = 0;
	virtual void remove(const T&) = 0;

	virtual bool contains(const T&) const = 0;
	virtual std::size_t find(const T&) const = 0;
	virtual std::size_t size() const = 0;

	virtual T& at(std::size_t index) = 0;
	virtual const T& at(std::size_t index) const = 0;

};

template<typename T> List<T>::~List() {}

template<typename T>
class Set {

public:
	virtual bool insert(const T&) = 0;
	virtual bool remove(const T&) = 0;
	virtual bool contains(const T&) const = 0;

	virtual void clear() = 0;
	virtual std::size_t size() const = 0;
	virtual List<T>* items() const = 0;

};

}

#endif
