//
// Created by Aleksandr Orlov on 09.04.2022.
//

#ifndef LAB3_CBUFFER_H
#define LAB3_CBUFFER_H
#include <iterator>
#include <algorithm>

template<class T>
class CBuffer {
public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *value_;
        T *arr_;
        int capacity_, size_ = 0;
    public:
        explicit Iterator(T *value, T *arr, int capacity) {
            value_ = value;
            arr_ = arr;
            capacity_ = capacity;
        }
        bool operator==(const Iterator &it) {
            return value_ == it.value_;
        }

        bool operator!=(const Iterator &it) {
            return value_ != it.value_;
        }

        T &operator*() {
            return *value_;
        }

        T *operator->() {
            return value_;
        }

        Iterator &operator=(T *it) {
            value_ = it;
            return *this;
        }

        Iterator operator++() {
            if (value_ == (arr_ + (capacity_ - 1)) && size_ != capacity_ - 1)
                value_ = arr_;
            else
                value_++;
            size_++;
            return *this;
        }

        Iterator operator--() {
            if (value_ == arr_ && size_ * (-1) != capacity_ - 1)
                value_ = arr_ + (capacity_ - 1);
            else
                value_--;
            size_--;
            return *this;
        }

        bool operator>(const Iterator &it) {
            return value_ > it.value_;
        }

        bool operator>=(const Iterator &it) {
            return value_ >= it.value_;
        }

        bool operator<(const Iterator &it) {
            return value_ < it.value_;
        }

        bool operator<=(const Iterator &it) {
            return value_ <= it.value_;
        }

        Iterator operator-(size_t i) {
            Iterator temp(*this);
            return temp -= i;
        }

        Iterator operator+(size_t i) {
            Iterator temp(*this);
            return temp += i;
        }

        std::ptrdiff_t operator-(Iterator const &it) {
            return this->value_ - it.value_;
        }

        std::ptrdiff_t operator+(Iterator const &it) {
            return this->value_ + it.value_;
        }

        Iterator operator+=(size_t i) {
            value_ = value_ + i;
            return *this;
        }

        Iterator operator-=(size_t i) {
            value_ = value_ - i;
            return *this;
        }

    };

    explicit CBuffer(int sz) {
        capacity_ = sz;
    }

    CBuffer(const CBuffer &cb) {
        capacity_ = cb.capacity_;
        size_ = cb.size_;
        std::copy(std::begin(cb.arr_), std::end(cb.arr_), std::begin(arr_));
        begin_ = cb.begin_;
        end_ = cb.end_;
    }

    ~CBuffer() {
        delete[] arr_;
    }

    Iterator begin() {
        if (size_ == capacity_)
            return Iterator(arr_, arr_, capacity_);
        if (begin_ + 1 == capacity_)
            return Iterator(arr_, arr_, capacity_);
        return Iterator(arr_ + begin_ + 1, arr_, capacity_);
    }

    Iterator end() {
        if (size_ == capacity_)
            return Iterator(arr_ + capacity_, arr_, capacity_);
        return Iterator(arr_ + end_, arr_, capacity_);
    }

    int size() const {
        return size_;
    }

    int capacity() const {
        return capacity_;
    }

    void push_back(const T& value) {
        if (size_ == capacity_)
            throw std::length_error("Not enough space");
        if (begin_ == end_ && capacity_ > 1) {
            arr_[end_] = value;
            begin_ = (--begin_ + capacity_) % capacity_;
            end_ = (++end_ + capacity_) % capacity_;
        }
        else {
            arr_[end_] = value;
            end_ = (++end_ + capacity_) % capacity_;
        }
        ++size_;
    }

    void pop_back() {
        if (size_ == 0)
            throw std::length_error("Already 0 elements in buffer");
        if (end_ == 0)
            end_ = capacity_ - 1;
        else
            end_--;
        size_--;
    }

    void push_front(const T& value) {
        if (size_ == capacity_)
            throw std::length_error("Not enough space");
        if (begin_ == end_ && capacity_ > 1) {
            arr_[begin_] = value;
            begin_ = (--begin_ + capacity_) % capacity_;
            end_ = (++end_ + capacity_) % capacity_;
        }
        else {
            arr_[begin_] = value;
            begin_ = (--begin_ + capacity_) % capacity_;
        }
        ++size_;
    }

    void pop_front() {
        if (size_ == 0)
            throw std::length_error("Already 0 elements in buffer");
        if (begin_ == capacity_ - 1)
            begin_ = 0;
        else
            begin_++;
        size_--;
    }

    T &operator[](size_t i) {
        if (i >= capacity_ || size_ == 0)
            throw std::length_error("Out of range");
        if (size_ == capacity_ && i < capacity_)
            return arr_[i];
        if (begin_ <= end_) {
            if (i < begin_ || i > end_)
                return arr_[i];
            else
                throw std::length_error("Out of range");
        }
        else {
            if (i > begin_ || i < end_)
                return arr_[i];
            else
                throw std::length_error("Out of range");
        }

    }

    void change_capacity(int value) {
        if (value == capacity_ || value < 0)
            return;

        T *newArr = new T[value];
        T *oldArr = arr_;

        if (capacity_ < value) {
            for (int i = 0; i < capacity_; i++)
                newArr[i] = arr_[i];
            capacity_ = value;
            arr_ = newArr;
            delete[] oldArr;
        }
        else {
            begin_ = 0, end_ = 0;
            capacity_ = value;
            size_ = 0;
            arr_ = newArr;
            delete[] oldArr;
        }
    }
private:
    int capacity_, size_ = 0;
    T *arr_ = new T[capacity_];
    int begin_ = 0, end_ = 0;
};

#endif //LAB3_CBUFFER_H
