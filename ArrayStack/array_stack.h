#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint> // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures {

template<typename T>
class ArrayStack {
public:
    ArrayStack();

    ArrayStack(std::size_t max);

    ~ArrayStack();

    void push(const T& data); // empilha

    T pop(); // desempilha

    T& top();

    void clear(); // limpa

    std::size_t size(); // tamanho

    std::size_t max_size();

    bool empty(); // vazia

    bool full(); // cheia

private:
    T* contents;
    int top_;
    std::size_t max_size_;

    const static auto DEFAULT_SIZE = 10u;
};

template<typename T>
ArrayStack<T>::ArrayStack()
{
    contents = new T[DEFAULT_SIZE];
    top_ = -1;
    max_size_ = DEFAULT_SIZE;
}

template<typename T>
ArrayStack<T>::ArrayStack(std::size_t max)
{
    contents = new T[max];
    top_ = -1;
    max_size_ = max;
}

template<typename T>
ArrayStack<T>::~ArrayStack()
{
    delete[] contents;
}

template<typename T>
void ArrayStack<T>::push(const T& data)
{
    if (full()) {
        throw std::out_of_range("Stack is full");
    } else {
        contents[++top_] = data;
    }
}

template<typename T>
T ArrayStack<T>::pop()
{
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    } else {
        return contents[top_--];
    }
}

template<typename T>
T& ArrayStack<T>::top()
{
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    } else {
        return contents[top_];
    }
}

template<typename T>
void ArrayStack<T>::clear()
{
    top_ = -1;
}

template<typename T>
std::size_t ArrayStack<T>::size()
{
    return top_ + 1;
}

template<typename T>
std::size_t ArrayStack<T>::max_size()
{
    return max_size_;
}

template<typename T>
bool ArrayStack<T>::empty()
{
    return top_ == -1;
}

template<typename T>
bool ArrayStack<T>::full()
{
    return top_ == max_size_ - 1;
}

}

#endif
