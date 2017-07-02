#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>
#include <memory>

#include <abstract.h>

#define DEFAULT_MAX 1000 // TODO implement variable sized ArrayList

namespace structures {

/**
 * @brief Implements a list(data structure), using arrays
 *
 * @tparam T Data type of the elements
 */
template<typename T>
class ArrayList : public List<T> {

public:

	/**
	 * @brief Default constructor
	 */
	ArrayList() = default;

	ArrayList(const ArrayList<T>& other):
		contents{copy_array(other.contents, other.max_size_)},
		size_{other.size_},
		max_size_{other.max_size_}
	{}

	ArrayList(ArrayList<T>&& other):
		contents{std::move(other.contents)},
		size_{std::move(other.size_)},
		max_size_{std::move(other.max_size_)}
	{}

	ArrayList<T>& operator=(const ArrayList<T>& other) {
		ArrayList<T> copy{other};
		std::swap(contents, copy.contents);
		std::swap(size_, copy.size_);
		std::swap(max_size_, copy.max_size_);
		return *this;
	}

	ArrayList<T>& operator=(ArrayList<T>&& other) {
		ArrayList<T> copy{std::move(other)};
		std::swap(contents, copy.contents);
		std::swap(size_, copy.size_);
		std::swap(max_size_, copy.max_size_);
		return *this;
	}

	/**
	 * @brief Constructor with a given maximum size
	 *
	 * @param max_size The maximum size of the list
	 */
	explicit ArrayList(std::size_t max_size):
		contents{new T[max_size]},
		max_size_{max_size} {}

	/**
	 * @brief Destroys the list
	 */
	~ArrayList() = default;

	/**
	 * @brief Clears the contents of the list
	 */
	void clear() {
		size_ = 0;
	}

	/**
	 * @brief Adds 'data' to the end of the list
	 *
	 * @param data The element that'll be added
	 */
	void push_back(const T& data) {
		insert(data, size_);
	}

	/**
	 * @brief Adds 'data' to the beginning of the list
	 *
	 * @param data The element that'll be added
	 */
	void push_front(const T& data) {
		insert(data, 0);
	}

	/**
	 * @brief Inserts at a given position of the list
	 *
	 * @param data The element that'll be inserted
	 * @param index The position where 'data' will be inserted
	 */
	void insert(const T& data, std::size_t index) {
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
	 * @brief Inserts the element sorted into the list
	 *
	 * @param data The element that'll be inserted
	 */
	void insert_sorted(const T& data) {
		std::size_t i = 0;
		while (i < size_ && data >= contents[i])
			i++;
		insert(data, i);
	}

	/**
	 * @brief Removes the element at the given position
	 *
	 * @param index The position of the element that'll be removed
	 *
	 * @return The element that was removed
	 */
	T erase(std::size_t index) {
		if (empty()) {
			throw std::out_of_range("List is empty");
		} else if (index >= size_) {
			throw std::out_of_range("Index out of bounds");
		} else {
			T deleted = contents[index];
			for (std::size_t i = index; i < size_ - 1; ++i) {
				contents[i] = contents[i+1];
			}
			size_--;
			return deleted;
		}
	}

	/**
	 * @brief Removes the element at the end of the list
	 *
	 * @return The element that was removed
	 */
	T pop_back() {
		return erase(size_ - 1);
	}

	/**
	 * @brief Removes the element at the beginning of the list
	 *
	 * @return The element that was removed
	 */
	T pop_front() {
		return erase(0);
	}

	/**
	 * @brief Removes 'data' from the list
	 *
	 * @param data The element that'll be removed
	 */
	void remove(const T& data) {
		erase(find(data));
	}

	/**
	 * @brief Checks if the list is full
	 *
	 * @return True if the list is full
	 */
	bool full() const {
		return size_ == max_size_;
	}

	/**
	 * @brief Checks if the list is empty
	 *
	 * @return True if the list is empty
	 */
	bool empty() const {
		return size_ == 0;
	}

	/**
	 * @brief Checks if the list contains an element(data)
	 *
	 * @param data The element that'll be checked if it is contained by the list
	 *
	 * @return True if the list contains 'data'
	 */
	bool contains(const T& data) const {
		return find(data) != size_;
	}

	/**
	 * @brief Returns the position of 'data' on the list
	 *
	 * @param data The element that'll be searched
	 *
	 * @return The position of 'data' on the list
	 */
	std::size_t find(const T& data) const {
		for (std::size_t i = 0; i < size_; ++i) {
			if (contents[i] == data)
				return i;
		}
		return size_;
	}

	/**
	 * @brief Size of the list
	 *
	 * @return Size of the list
	 */
	std::size_t size() const {
		return size_;
	}

	/**
	 * @brief Maximum size of the list
	 *
	 * @return Maximum size of the list
	 */
	std::size_t max_size() const {
		return max_size_;
	}

	/**
	 * @brief Checks if the index is valid, then returns a reference to the
	 * element at the given index of the list
	 *
	 * @param index The index on the list of the element that'll be returned
	 *
	 * @return A reference to the element at the given index
	 */
	T& at(std::size_t index) {
		return const_cast<T&>(static_cast<const ArrayList*>(this)->at(index));
	}

	const T& at(std::size_t index) const {
		if (index >= size_) {
			throw std::out_of_range("Index out of bounds");
		} else {
			return contents[index];
		}
	}

	/**
	 * @brief Overloads the operator '[]'
	 * @details Returns a reference to the element at 'index' position of the
	 * list
	 *
	 * @param index The index on the list of the element that'll be returned
	 *
	 * @return A reference to the element at the given index
	 */
	T& operator[](std::size_t index) {
		return const_cast<T&>(
				static_cast<const ArrayList*>(this)->operator[](index));
	}

	const T& operator[](std::size_t index) const {
		return contents[index];
	}

private:

	static std::unique_ptr<T[]> copy_array(const std::unique_ptr<T[]>& original,
			std::size_t size) {
		std::unique_ptr<T[]> copy{new T[size]};
		for (std::size_t i = 0; i < size; i++) {
			copy[i] = original[i];
		}
		return copy;
	}

	std::unique_ptr<T[]> contents{new T[DEFAULT_MAX]};
	std::size_t size_{0u};
	std::size_t max_size_{DEFAULT_MAX};

};

}  // namespace structures

#endif
