#ifndef STACK_HPP
#define STACK_HPP

#include "Container.hpp"

template<typename T>
class Stack {
private:
    Container<T> container;

public:
    Stack() = default;

    void push(const T& element) {
        container.add(element);
    }

    void pop() {
        container.removeLast(); // Remove o último elemento
    }

    T top() const {
        if (!isEmpty()) {
            return container.get(container.getSize() - 1);
        } else {
            throw std::underflow_error("Stack is empty");
        }
    }

    bool isEmpty() const {
        return container.getSize() == 0;
    }
};

#endif // STACK_HPP