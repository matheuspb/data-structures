#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures {

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
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    const static auto DEFAULT_SIZE = 10u;
};

}

#endif
