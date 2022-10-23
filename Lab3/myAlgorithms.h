//
// Created by Aleksandr Orlov on 10.04.2022.
//

#ifndef LAB3_MYALGORITHMS_H
#define LAB3_MYALGORITHMS_H

namespace orlov {
    template<class T, class V>
    bool all_of(T begin, T end, V pred) {
        while (begin != end) {
            if (!pred(*begin))
                return false;
            ++begin;
        }
        return true;
    }

    template<class T, class V>
    bool any_of(T begin, T end, V pred) {
        while (begin != end) {
            if (pred(*begin))
                return true;
            ++begin;
        }
        return false;
    }

    template<class T, class V>
    bool none_of(T begin, T end, V pred) {
        while (begin != end) {
            if (pred(*begin))
                return false;
            ++begin;
        }
        return true;
    }

    template<class T, class V>
    bool one_of(T begin, T end, V pred) {
        while (begin != end) {
            if (pred(*begin))
                break;
            ++begin;
        }

        if (begin == end)
            return false;
        return orlov::none_of(++begin, end, pred);
    }

    template<class T>
    bool is_sorted(T begin, T end) {
        if (begin == end)
            return true;

        T next = begin;

        while (++next != end) {
            if (*next < *begin)
                return false;
            ++begin;
        }
        return true;
    }

    template<class T, class V>
    bool is_partitioned(T begin, T end, V pred) {
        while (begin != end && pred(*begin)) {
            ++begin;
        }
        while (begin != end) {
            if (pred(*begin))
                return false;
            ++begin;
        }
        return true;
    }

    template<class T, class V>
    T find_not(T begin, T end, V pred) {
        while (begin != end) {
            if (!pred(*begin))
                return begin;
            ++begin;
        }
        return end;
    }

    template<class T, class V>
    T find_backward(T begin, T end, V pred) {
        T tmp = end;

        --begin, --end;
        while (end != begin) {
            if (pred(*end))
                return end;
            --end;
        }
        return tmp;
    }

    template<typename T, typename V>
    bool is_palindrome(T begin, T end, V pred) {
        if (begin == end)
            return true;
        --end;
        while (begin != end) {
            if (!pred(*begin, *end))
                return false;
            ++begin;
            if (begin == end)
                break;
            --end;
        }
        return true;
    }
}

#endif //LAB3_MYALGORITHMS_H
