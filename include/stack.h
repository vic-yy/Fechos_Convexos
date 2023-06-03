#ifndef STACK_H
#define STACK_H

#include <cstddef>  // Include the <cstddef> header for size_t

template <typename T>
class stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value, Node* nextNode = nullptr)
            : data(value), next(nextNode) {}
    };

    Node* topNode;
    size_t stackSize;

public:
    stack() : topNode(nullptr), stackSize(0) {}

    ~stack() {
        while (!empty()) {
            pop();
        }
    }

    bool empty() const {
        return topNode == nullptr;
    }

    size_t size() const {
        return stackSize;
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("Stack is empty.");
        }
        return topNode->data;
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Stack is empty.");
        }
        return topNode->data;
    }

    void push(const T& value) {
        Node* newNode = new Node(value, topNode);
        topNode = newNode;
        stackSize++;
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty.");
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        stackSize--;
    }

    T& operator[](size_t index) {
        if (index >= stackSize) {
            throw std::out_of_range("Index out of range.");
        }
        Node* current = topNode;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](size_t index) const {
        if (index >= stackSize) {
            throw std::out_of_range("Index out of range.");
        }
        Node* current = topNode;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
};

#endif  // STACK_H
