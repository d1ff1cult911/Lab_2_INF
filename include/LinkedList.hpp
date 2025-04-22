#pragma once
#include "Exceptions.hpp"
#include <memory>
#include <initializer_list>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        Node(T data) : data(data), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    int size = 0;

    Node* GetNode(int index) const {
        if (index < 0 || index >= size) throw IndexOutOfRange();
        Node* current = head.get();
        for (int i = 0; i < index; ++i) {
            current = current->next.get();
        }
        return current;
    }

public:
    // Конструкторы
    LinkedList() = default;

    LinkedList(std::initializer_list<T> items) {
        for (auto it = items.end() - 1; it >= items.begin(); --it) {
            Prepend(*it);
        }
    }

    LinkedList(const LinkedList& other) {
        if (!other.head) {
            head.reset();
            size = 0;
            return;
        }
        
        head = std::make_unique<Node>(other.head->data);
        Node* src = other.head->next.get();
        Node* dst = head.get();
        size = other.size;
        
        while (src) {
            dst->next = std::make_unique<Node>(src->data);
            dst = dst->next.get();
            src = src->next.get();
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            LinkedList temp(other);
            std::swap(head, temp.head);
            std::swap(size, temp.size);
        }
        return *this;
    }

    // Исправленный метод GetSubList
    LinkedList<T> GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex >= size || startIndex > endIndex) {
            throw IndexOutOfRange();
        }
        
        LinkedList<T> result;
        Node* current = GetNode(startIndex);
        for (int i = startIndex; i <= endIndex; ++i) {
            result.Append(current->data);
            current = current->next.get();
        }
        return result;
    }

    void Prepend(T item) {
        auto newNode = std::make_unique<Node>(item);
        newNode->next = std::move(head);
        head = std::move(newNode);
        size++;
    }

    void Append(T item) {
        auto newNode = std::make_unique<Node>(item);
        if (!head) {
            head = std::move(newNode);
        } else {
            GetNode(size - 1)->next = std::move(newNode);
        }
        size++;
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > size) throw IndexOutOfRange();
        
        if (index == 0) return Prepend(item);
        if (index == size) return Append(item);

        Node* prev = GetNode(index - 1);
        auto newNode = std::make_unique<Node>(item);
        newNode->next = std::move(prev->next);
        prev->next = std::move(newNode);
        size++;
    }

    T GetFirst() const {
        if (size == 0) throw IndexOutOfRange();
        return head->data;
    }

    T GetLast() const {
        return Get(size - 1);
    }

    T Get(int index) const {
        return GetNode(index)->data;
    }

    int GetLength() const {
        return size;
    }

    LinkedList<T>* Concat(const LinkedList<T>& other) const {
        LinkedList<T> result(*this);
        Node* current = other.head.get();
        while (current) {
            result.Append(current->data);
            current = current->next.get();
        }
        return result;
    }

    // Удаление элементов
    void RemoveFirst() {
        if (size == 0) throw IndexOutOfRange();
        head = std::move(head->next);
        size--;
    }

    void RemoveLast() {
        if (size == 0) throw IndexOutOfRange();
        if (size == 1) return RemoveFirst();
        
        Node* prev = GetNode(size - 2);
        prev->next.reset();
        size--;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) throw IndexOutOfRange();
        if (index == 0) return RemoveFirst();
        
        Node* prev = GetNode(index - 1);
        prev->next = std::move(prev->next->next);
        size--;
    }
};
