#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures {

/**
 * @brief Implements a Queue(data structure), using arrrays.
 * @details This data structure works like a real 'queue', you add(enqueue)
 * elements to the end of the queue, and remove(dequeue) from the beginning.
 * It follow the FIFO(first in, first out) principle.
 *
 * @tparam T This is the data type of the elements of the queue.
 */
template<typename T>
class ArrayQueue {
public:
    ArrayQueue();

    ArrayQueue(std::size_t max);

    ~ArrayQueue();

    void enqueue(const T& data);

    T dequeue();

    T& back();

    void clear();

    std::size_t size();

    std::size_t max_size();

    bool empty();

    bool full();

private:
    T* contents; /**< The array that'll contain the elements */
    std::size_t size_; /**< Current size of the queue */
    std::size_t max_size_; /**< Maximum size of the queue */

    const static auto DEFAULT_SIZE = 10u;
};

/**
 * @brief Default constructor
 * @details Constructs the queue with the default size
 *
 * @tparam T Data type of the elements
 */
template<typename T>
ArrayQueue<T>::ArrayQueue()
{
    contents = new T[DEFAULT_SIZE];
    size_ = 0;
    max_size_ = DEFAULT_SIZE;
}

/**
 * @brief Constructor with a given maximum size of the queue
 * @details Constructs the queue with 'max' size
 *
 * @param max Maximum size of the queue
 * @tparam T Data type of the elements
 */
template<typename T>
ArrayQueue<T>::ArrayQueue(std::size_t max)
{
    contents = new T[max];
    size_ = 0;
    max_size_ = max;
}

/**
 * @brief Destructor
 * @details Deletes the 'contents' array
 *
 * @tparam T Data type of the elements
 */
template<typename T>
ArrayQueue<T>::~ArrayQueue()
{
    delete[] contents;
}

/**
 * @brief Adds 'data' to the end of the queue
 * @details Checks if the queue is not full, then puts 'data' at the end of the
 * queue. Throws std::out_of_range if the queue is full
 *
 * @param data The element that'll be added to the queue
 * @tparam T Data type of the elements
 */
template<typename T>
void ArrayQueue<T>::enqueue(const T& data)
{
    if (full()) {
        throw std::out_of_range("Queue is full");
    } else {
        contents[size_++] = data;
    }
}

/**
 * @brief Removes the element at the beginning of the queue
 * @details Checks if the queue is not empty, then returns and removes the first
 * element of the queue. Throws std::out_of_range if the queue is empty
 *
 * @tparam T Data type of the elements
 * @return The element that was removed
 */
template<typename T>
T ArrayQueue<T>::dequeue()
{
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    } else {
        T first = contents[0];
        for (int i = 1; i < size(); ++i) {
            contents[i-1] = contents[i];
        }
        size_--;
        return first;
    }
}

/**
 * @brief Returns a reference to the last element of the queue
 * @details Checks if the queue is not empty, then returns a reference to the
 * element at the end of the queue. Throws std::out_of_range if the queue is
 * empty
 *
 * @tparam T Data type of the elements
 * @return A reference to the alst element of the queue
 */
template<typename T>
T& ArrayQueue<T>::back()
{
    if (empty()) {
        throw std::out_of_range("Queue is empty");
    } else {
        return contents[size_-1];
    }
}

/**
 * @brief Clears the queue
 *
 * @tparam T Data type of the elements
 */
template<typename T>
void ArrayQueue<T>::clear()
{
    size_ = 0;
}

/**
 * @brief Returns the number of elements on the queue
 *
 * @tparam T Data type of the elements
 */
template<typename T>
std::size_t ArrayQueue<T>::size()
{
    return size_;
}

/**
 * @brief Returns the maximum size of the queue
 *
 * @tparam T Data type of the elements
 */
template<typename T>
std::size_t ArrayQueue<T>::max_size()
{
    return max_size_;
}

/**
 * @brief Checks if the queue is empty
 *
 * @tparam T Data type of the elements
 * @return True if queue is empty
 */
template<typename T>
bool ArrayQueue<T>::empty()
{
    return size_ == 0;
}

/**
 * @brief Checks if queue is full
 *
 * @tparam T Data type of the elements
 * @return True if queue is full
 */
template<typename T>
bool ArrayQueue<T>::full()
{
    return size_ == max_size_;
}

}

#endif
