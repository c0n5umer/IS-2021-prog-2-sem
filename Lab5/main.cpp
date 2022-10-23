#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include "allocator.h"

int main() {
    clock_t start, end;
    std::cout << std::fixed;

    // Vector test
    std::vector<int, OrlovAllocator<int>> cvec;
    std::vector<int> vec;

    start = clock();
    cvec.emplace_back(1);
    end = clock();
    std::cout << "Custom alloc vector time is " << (double)(end - start) / CLOCKS_PER_SEC << " s\n";

    start = clock();
    vec.emplace_back(1);
    end = clock();
    std::cout << "Std alloc vector time is " << (double)(end - start) / CLOCKS_PER_SEC << " s\n";

    // String test
    std::basic_string<char, std::char_traits<char>, OrlovAllocator<char>> cstr;
    std::basic_string<char, std::char_traits<char>, std::allocator<char>> str;

    start = clock();
    cstr = "test string for test";
    end = clock();
    std::cout << "Custom alloc string time is " << (double)(end - start) / CLOCKS_PER_SEC << " s\n";

    start = clock();
    str = "test string for test";
    end = clock();
    std::cout << "Std alloc string time is " << (double)(end - start) / CLOCKS_PER_SEC << " s\n";

    // List test
    std::list<int, OrlovAllocator<int>> cl;
    std::list<int> l;

    start = clock();
    cl.push_back(1);
    end = clock();
    std::cout << "Custom alloc list time is " << (double)(end - start) / CLOCKS_PER_SEC << " s\n";

    start = clock();
    l.push_back(1);
    end = clock();
    std::cout << "Std alloc list time is " << (double)(end - start) / CLOCKS_PER_SEC << " s\n";

    // Set list
    std::set<int, std::less<>, OrlovAllocator<int>> cset;
    std::set<int, std::less<>, OrlovAllocator<int>> set;

    start = clock();
    cset.insert(1);
    end = clock();
    std::cout << "Custom alloc set time is " << (double)(end - start) / CLOCKS_PER_SEC << " s\n";

    start = clock();
    set.insert(1);
    end = clock();
    std::cout << "Std alloc set time is " << (double)(end - start) / CLOCKS_PER_SEC << " s\n";
    return 0;
}
