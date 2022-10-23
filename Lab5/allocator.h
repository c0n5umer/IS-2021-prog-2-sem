//
// Created by Aleksandr Orlov on 12.05.2022.
//

#ifndef LAB5_ALLOCATOR_H
#define LAB5_ALLOCATOR_H

#define INIT_SIZE 52428800

template<class T>
class OrlovAllocator {
public:
    typedef T value_type;

    OrlovAllocator() {
        ptr = (T*)malloc(INIT_SIZE);
        w_ptr = ptr;
    }

    ~OrlovAllocator() {
        free(ptr);
    }

    template<class U>
    constexpr OrlovAllocator(const OrlovAllocator<U> &)  : OrlovAllocator() {}

    T *allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
            throw std::bad_array_new_length();

        if (bytes + n * sizeof(T) > INIT_SIZE)
            throw std::bad_alloc();

        w_ptr += n;
        bytes += n * sizeof(T);
        return w_ptr;
    }

    void deallocate(T *p, std::size_t n) {
    }

private:
    T *ptr;
    T *w_ptr;
    int bytes = 0;
};

template<class T, class U>
bool operator==(const OrlovAllocator<T> &, const OrlovAllocator<U> &) { return true; }

template<class T, class U>
bool operator!=(const OrlovAllocator<T> &, const OrlovAllocator<U> &) { return false; }

#endif //LAB5_ALLOCATOR_H
