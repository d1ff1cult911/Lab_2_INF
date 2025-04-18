#pragma once
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include <memory>
#include <stdexcept>

template <typename T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual int GetLength() const = 0;

    // Immutable operations
    virtual std::unique_ptr<Sequence<T>> Append(T item) const = 0;
    virtual std::unique_ptr<Sequence<T>> Prepend(T item) const = 0;
    virtual std::unique_ptr<Sequence<T>> InsertAt(T item, int index) const = 0;
    virtual std::unique_ptr<Sequence<T>> Concat(const Sequence<T>& other) const = 0;

    // Mutable operations
    virtual void AppendMutable(T item) = 0;
    virtual void PrependMutable(T item) = 0;
    virtual void InsertAtMutable(T item, int index) = 0;

    virtual ~Sequence() = default;
};
template <typename T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> list;

public:
    ListSequence() = default;
    ListSequence(const LinkedList<T>& lst) : list(lst) {}

    T GetFirst() const override {
        if(list.GetLength() == 0) throw IndexOutOfRange();
        return list.Get(0);
    }

    T GetLast() const override {
        if(list.GetLength() == 0) throw IndexOutOfRange();
        return list.Get(list.GetLength()-1);
    }

    T Get(int index) const override {
        return list.Get(index);
    }

    int GetLength() const override {
        return list.GetLength();
    }

    // Immutable operations
    std::unique_ptr<Sequence<T>> Append(T item) const override {
        LinkedList<T> newList = list;
        newList.Append(item);
        return std::make_unique<ListSequence>(newList);
    }

    std::unique_ptr<Sequence<T>> Prepend(T item) const override {
        LinkedList<T> newList = list;
        newList.Prepend(item);
        return std::make_unique<ListSequence>(newList);
    }

    std::unique_ptr<Sequence<T>> InsertAt(T item, int index) const override {
        LinkedList<T> newList = list;
        newList.InsertAt(item, index);
        return std::make_unique<ListSequence>(newList);
    }

    std::unique_ptr<Sequence<T>> Concat(const Sequence<T>& other) const override {
        LinkedList<T> newList = list;
        for(int i = 0; i < other.GetLength(); ++i) {
            newList.Append(other.Get(i));
        }
        return std::make_unique<ListSequence>(newList);
    }

    // Mutable operations
    void AppendMutable(T item) override {
        list.Append(item);
    }

    void PrependMutable(T item) override {
        list.Prepend(item);
    }

    void InsertAtMutable(T item, int index) override {
        list.InsertAt(item, index);
    }
};
template <typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> array;

public:
    ArraySequence() = default;
    ArraySequence(const DynamicArray<T>& arr) : array(arr) {}

    // Реализация базовых методов
    T GetFirst() const override {
        if (array.GetSize() == 0) throw IndexOutOfRange();
        return array.Get(0);
    }

    T GetLast() const override {
        if (array.GetSize() == 0) throw IndexOutOfRange();
        return array.Get(array.GetSize() - 1);
    }

    T Get(int index) const override {
        return array.Get(index);
    }

    int GetLength() const override {
        return array.GetSize();
    }

    // Immutable методы
    std::unique_ptr<Sequence<T>> Append(T item) const override {
        DynamicArray<T> newArray = array;
        newArray.Resize(newArray.GetSize() + 1);
        newArray.Set(newArray.GetSize() - 1, item);
        return std::make_unique<ArraySequence>(newArray);
    }

    std::unique_ptr<Sequence<T>> Prepend(T item) const override {
        DynamicArray<T> newArray(array.GetSize() + 1);
        newArray.Set(0, item);
        for (int i = 0; i < array.GetSize(); ++i) {
            newArray.Set(i + 1, array.Get(i));
        }
        return std::make_unique<ArraySequence>(newArray);
    }

    std::unique_ptr<Sequence<T>> InsertAt(T item, int index) const override {
        if (index < 0 || index > array.GetSize()) throw IndexOutOfRange();
        DynamicArray<T> newArray(array.GetSize() + 1);
        for (int i = 0; i < index; ++i) newArray.Set(i, array.Get(i));
        newArray.Set(index, item);
        for (int i = index; i < array.GetSize(); ++i) newArray.Set(i + 1, array.Get(i));
        return std::make_unique<ArraySequence>(newArray);
    }

    std::unique_ptr<Sequence<T>> Concat(const Sequence<T>& other) const override {
        DynamicArray<T> newArray(array.GetSize() + other.GetLength());
        for (int i = 0; i < array.GetSize(); ++i) newArray.Set(i, array.Get(i));
        for (int i = 0; i < other.GetLength(); ++i) newArray.Set(array.GetSize() + i, other.Get(i));
        return std::make_unique<ArraySequence>(newArray);
    }

    // Mutable методы
    void AppendMutable(T item) override {
        array.Resize(array.GetSize() + 1);
        array.Set(array.GetSize() - 1, item);
    }

    void PrependMutable(T item) override {
        DynamicArray<T> newArray(array.GetSize() + 1);
        newArray.Set(0, item);
        for (int i = 0; i < array.GetSize(); ++i) newArray.Set(i + 1, array.Get(i));
        array = newArray;
    }

    void InsertAtMutable(T item, int index) override {
        if (index < 0 || index > array.GetSize()) throw IndexOutOfRange();
        DynamicArray<T> newArray(array.GetSize() + 1);
        for (int i = 0; i < index; ++i) newArray.Set(i, array.Get(i));
        newArray.Set(index, item);
        for (int i = index; i < array.GetSize(); ++i) newArray.Set(i + 1, array.Get(i));
        array = newArray;
    }
};