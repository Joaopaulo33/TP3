#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <stdexcept>

template<typename T>
class Container {
private:
    T* data;
    int size;
    int capacity;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Container() : size(0), capacity(10) {
        data = new T[capacity];
    }

    ~Container() {
        delete[] data;
    }

    void add(T item) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = item;
    }

    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    void removeLast() {
        if (size > 0) {
            --size;
        } else {
            throw std::underflow_error("Container is empty");
        }
    }

    void swap(int i, int j) {
        if (i < 0 || i >= size || j < 0 || j >= size) {
            throw std::out_of_range("Index out of range");
        }
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
};

#endif // CONTAINER_HPP