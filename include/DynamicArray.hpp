#pragma once
#include "Exceptions.hpp"
#include <algorithm>
#include <memory>

template <typename T>
class DynamicArray {
private:
    int capacity;
    std::unique_ptr<T[]> data;
    
public:
    DynamicArray(int size = 0) : capacity(size), data(std::make_unique<T[]>(size)) {}

    DynamicArray(const T* items, int count) : DynamicArray(count) {
        for(int i = 0; i < count; ++i) data[i] = items[i];
    }

    DynamicArray(const DynamicArray& other) : DynamicArray(other.capacity) {
        std::copy(other.data.get(), other.data.get() + capacity, data.get());
    }

    T Get(int index) const {
        if(index < 0 || index >= capacity) throw IndexOutOfRange();
        return data[index];
    }

    int GetSize() const { return capacity; }

    void Set(int index, T value) {
        if(index < 0 || index >= capacity) throw IndexOutOfRange();
        data[index] = value;
    }

    void Resize(int newSize) {
        std::unique_ptr<T[]> newData = std::make_unique<T[]>(newSize);
        int elementsToCopy = std::min(capacity, newSize);
        std::copy(data.get(), data.get() + elementsToCopy, newData.get());
        data.swap(newData);
        capacity = newSize;
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if(this != &other) {
            Resize(other.capacity);
            std::copy(other.data.get(), other.data.get() + capacity, data.get());
        }
        return *this;
    }
};