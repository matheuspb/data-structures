// Copyright 2016 Matheus Bittencourt

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

/**
 * @brief Implements a list(data structure), using arrays
 *
 * @tparam T Data type of the elements
 */
template<typename T>
class ArrayList {
public:
	/**
	@brief Default constructor
	*/
	ArrayList() = default;
	explicit ArrayList(std::size_t max_size);
	~ArrayList();

	void clear();
	void push_back(T data);
	void push_front(T data);
	void insert(T data, std::size_t index);
	void insert_sorted(T data);
	T pop(std::size_t index);
	T pop_back();
	T pop_front();
	void remove(T data);
	bool full() const;
	bool empty() const;
	bool contains(const T& data) const;
	std::size_t find(const T& data) const;
	std::size_t size() const;
	std::size_t max_size() const;
	T& at(std::size_t index);
	T& operator[](std::size_t index);
	const T& at(std::size_t index) const;
	const T& operator[](std::size_t index) const;

private:
	T* contents{new T[DEFAULT_MAX]};
	std::size_t size_{0u};
	std::size_t max_size_{DEFAULT_MAX};

	static const auto DEFAULT_MAX{10u};
};

/**
 * @brief Constructor with a given maximum size
 *
 * @param max_size The maximum size of the list
 * @tparam T Data type of the elements
 */
template<typename T>
ArrayList<T>::ArrayList(std::size_t max_size):
	contents{new T[max_size]},
	max_size_{max_size} {}

/**
 * @brief Destroys the list
 *
 * @tparam T Data type of the elements
 */
template<typename T>
ArrayList<T>::~ArrayList() {
	delete [] contents;
}

/**
 * @brief Clears the contents of the list
 *
 * @tparam T Data type of the elements
 */
template<typename T>
void ArrayList<T>::clear() {
	size_ = 0;
}

/**
 * @brief Adds 'data' to the end of the list
 *
 * @tparam T Data type of the elements
 * @param data The element that'll be added
 */
template<typename T>
void ArrayList<T>::push_back(T data) {
	insert(data, size_);
}

/**
 * @brief Adds 'data' to the beginning of the list
 *
 * @tparam T Data type of the elements
 * @param data The element that'll be added
 */
template<typename T>
void ArrayList<T>::push_front(T data) {
	insert(data, 0);
}

/**
 * @brief Inserts at a given position of the list
 *
 * @tparam T Data type of the elements
 * @param data The element that'll be inserted
 * @param index The position where 'data' will be inserted
 */
template<typename T>
void ArrayList<T>::insert(T data, std::size_t index) {
	if (full()) {
		throw std::out_of_range("List is full");
	} else if (index > size_) {
		throw std::out_of_range("Index out of bounds");
	} else {
		for (std::size_t i = size_; i > index; i--) {
			contents[i] = contents[i-1];
		}
		contents[index] = data;
		size_++;
	}
}

/**
 * @brief Inserts the element sorted
 *
 * @tparam T Data type of the elements
 * @param data The element that'll be inserted
 */
template<typename T>
void ArrayList<T>::insert_sorted(T data) {
	std::size_t i = 0;
	while (i < size_ && data >= contents[i])
		i++;
	insert(data, i);
}

/**
 * @brief Removes the element at the given position
 *
 * @tparam T Data type of the elements
 * @param index The position of the element that'll be removed
 * @return The element that was removed
 */
template<typename T>
T ArrayList<T>::pop(std::size_t index) {
	T deleted = contents[index];
	if (empty()) {
		throw std::out_of_range("List is empty");
	} else if (index >= size_) {
		throw std::out_of_range("Index out of bounds");
	} else {
		for (std::size_t i = index; i < size_ - 1; ++i) {
			contents[i] = contents[i+1];
		}
		size_--;
	}
	return deleted;
}

/**
 * @brief Removes the element at the end of the list
 *
 * @tparam T Data type of the elements
 * @return The element that was removed
 */
template<typename T>
T ArrayList<T>::pop_back() {
	return pop(size_ - 1);
}

/**
 * @brief Removes the element at the beginning of the list
 *
 * @tparam T Data type of the elements
 * @return The element that was removed
 */
template<typename T>
T ArrayList<T>::pop_front() {
	return pop(0);
}

/**
 * @brief Removes 'data' from the list
 *
 * @tparam T Data type of the elements
 * @param data The element that'll be removed
 */
template<typename T>
void ArrayList<T>::remove(T data) {
	pop(find(data));
}

/**
 * @brief Checks if the list is full
 *
 * @tparam T Data type of the elements
 * @return True if the list is full
 */
template<typename T>
bool ArrayList<T>::full() const {
	return size_ == max_size_;
}

/**
 * @brief Checks if the list is empty
 *
 * @tparam T Data type of the elements
 * @return True if the list is empty
 */
template<typename T>
bool ArrayList<T>::empty() const {
	return size_ == 0;
}

/**
 * @brief Checks if the list contains an element(data)
 *
 * @tparam T Data type of the elements
 * @param data The element that'll be checked if it is contained by the list
 * @return True if the list contains 'data'
 */
template<typename T>
bool ArrayList<T>::contains(const T& data) const {
	for (std::size_t i = 0; i < size_ + 1; ++i) {
		if (contents[i] == data)
			return true;
	}
	return false;
}

/**
 * @brief Returns the position of 'data' on the list
 *
 * @tparam T Data type of the elements
 * @param data The element that'll be searched
 * @return The position of 'data' on the list
 */
template<typename T>
std::size_t ArrayList<T>::find(const T& data) const {
	for (std::size_t i = 0; i < size_; ++i) {
		if (contents[i] == data)
			return i;
	}
	return size_;
}

/**
 * @brief Size of the list
 *
 * @tparam T Data type of the elements
 * @return Size of the list
 */
template<typename T>
std::size_t ArrayList<T>::size() const {
	return size_;
}

/**
 * @brief Maximum size of the list
 *
 * @tparam T Data type of the elements
 * @return Maximum size of the list
 */
template<typename T>
std::size_t ArrayList<T>::max_size() const {
	return max_size_;
}

/**
 * @brief Checks if the index is valid, then returns a reference to the element
 * at the given index of the list
 *
 * @tparam T Data type of the elements
 * @param index The index on the list of the element that'll be returned
 * @return A reference to the element at the given index
 */
template<typename T>
T& ArrayList<T>::at(std::size_t index) {
	if (index >= size_) {
		throw std::out_of_range("Index out of bounds");
	} else {
		return contents[index];
	}
}

/**
 * @brief Overloads the operator '[]'
 * @details Returns a reference to the element at 'index' position of the list
 *
 * @tparam T Data type of the elements
 * @param index The index on the list of the element that'll be returned
 * @return A reference to the element at the given index
 */
template<typename T>
T& ArrayList<T>::operator[](std::size_t index) {
	return contents[index];
}

/**
 * @brief Checks if the index is valid, then returns a reference to the element
 * at the given index of the list
 *
 * @tparam T Data type of the elements
 * @param index The index on the list of the element that'll be returned
 * @return A reference to the element at the given index
 */
template<typename T>
const T& ArrayList<T>::at(std::size_t index) const {
	if (index >= size_) {
		throw std::out_of_range("Index out of bounds");
	} else {
		return contents[index];
	}
}

/**
 * @brief Overloads the operator '[]'
 * @details Returns a reference to the element at 'index' position of the list
 *
 * @tparam T Data type of the elements
 * @param index The index on the list of the element that'll be returned
 * @return A reference to the element at the given index
 */
template<typename T>
const T& ArrayList<T>::operator[](std::size_t index) const {
	return contents[index];
}

}  // namespace structures

#endif
