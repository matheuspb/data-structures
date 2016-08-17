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

}

#endif
