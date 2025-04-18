#include <iostream>
#include "Sequence.hpp"
#include "LinkedList.hpp"

void TestDynamicArray() {
    try {
        std::cout << "\n=== Testing DynamicArray ===\n";
        DynamicArray<int> arr(3);
        arr.Set(0, 10);
        arr.Set(1, 20);
        arr.Set(2, 30);

        // Basic operations
        std::cout << "Test 1: " << (arr.Get(1) == 20 ? "PASSED" : "FAILED") << "\n";
        std::cout << "Test 2: " << (arr.GetSize() == 3 ? "PASSED" : "FAILED") << "\n";

        // Resize
        arr.Resize(5);
        std::cout << "Test 3: " << (arr.GetSize() == 5 ? "PASSED" : "FAILED") << "\n";

    } catch (...) {
        std::cout << "DynamicArray tests FAILED\n";
    }
}

void TestLinkedList() {
    try {
        std::cout << "\n=== Testing LinkedList ===\n";
        LinkedList<int> list;
        list.Append(10);
        list.Prepend(5);
        list.InsertAt(7, 1);

        // Basic operations
        std::cout << "Test 1: " << (list.Get(0) == 5 ? "PASSED" : "FAILED") << "\n";
        std::cout << "Test 2: " << (list.Get(1) == 7 ? "PASSED" : "FAILED") << "\n";
        std::cout << "Test 3: " << (list.GetLength() == 3 ? "PASSED" : "FAILED") << "\n";
        LinkedList<int> sub = list.GetSubList(1, 2);
        std::cout << "Test 4: " << (sub.GetLength() == 2 ? "PASSED" : "FAILED") << "\n";
    } catch (...) {
        std::cout << "LinkedList tests FAILED\n";
    }
}

void TestArraySequence() {
    try {
        std::cout << "\n=== Testing ArraySequence ===\n";
        ArraySequence<int> seq;
        seq.AppendMutable(10);
        seq.PrependMutable(5);
        seq.InsertAtMutable(7, 1);

        // Mutable operations
        std::cout << "Test 1: " << (seq.Get(1) == 7 ? "PASSED" : "FAILED") << "\n";
        std::cout << "Test 2: " << (seq.GetLength() == 3 ? "PASSED" : "FAILED") << "\n";

        // Immutable operations
        auto newSeq = seq.Append(20);
        std::cout << "Test 3: " << (newSeq->GetLength() == 4 ? "PASSED" : "FAILED") << "\n";
        std::cout << "Test 4: " << (seq.GetLength() == 3 ? "PASSED" : "FAILED") << "\n";

    } catch (...) {
        std::cout << "ArraySequence tests FAILED\n";
    }
}

void TestListSequence() {
    try {
        std::cout << "\n=== Testing ListSequence ===\n";
        ListSequence<int> seq;
        seq.AppendMutable(10);
        seq.PrependMutable(5);
        seq.InsertAtMutable(7, 1);

        std::cout << "Test 1: " << (seq.Get(1) == 7 ? "PASSED" : "FAILED") << "\n";
        std::cout << "Test 2: " << (seq.GetLength() == 3 ? "PASSED" : "FAILED") << "\n";

        auto concated = seq.Concat(*seq.Append(20));
        std::cout << "Test 3: " << (concated->GetLength() == 7 ? "PASSED" : "FAILED") << "\n";

    } catch (...) {
        std::cout << "ListSequence tests FAILED\n";
    }
}

void TestExceptions() {
    try {
        std::cout << "\n=== Testing Exceptions ===\n";
        DynamicArray<int> arr(0);
        arr.Get(0); // Should throw
        std::cout << "Test 1: FAILED\n";
    } catch (const IndexOutOfRange&) {
        std::cout << "Test 1: PASSED\n";
    }
}

int main() {
    TestDynamicArray();
    TestLinkedList();
    TestArraySequence();
    TestListSequence();
    TestExceptions();
    
    std::cout << "\n=== All tests completed ===\n";
    return 0;
}