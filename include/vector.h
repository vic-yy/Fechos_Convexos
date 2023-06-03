#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <algorithm>

template <typename T>
class Vector {
public:
    Vector() : capacity_(kDefaultCapacity), size_(0) {
        data_ = new T[kDefaultCapacity];
    }

    Vector(const Vector& other) : capacity_(other.size_), size_(other.size_) {
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            capacity_ = other.size_;
            size_ = other.size_;
            data_ = new T[capacity_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }

    ~Vector() {
        delete[] data_;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            ExpandCapacity();
        }
        data_[size_] = value;
        size_++;
    }

    void pop_back() {
        if (size_ > 0) {
            size_--;
        }
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

private:
    static const size_t kDefaultCapacity = 10;
    static const size_t kGrowthFactor = 2;

    T* data_;
    size_t capacity_;
    size_t size_;

    void ExpandCapacity() {
        capacity_ *= kGrowthFactor;
        T* new_data = new T[capacity_];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
    }
};

#endif // VECTOR_H
