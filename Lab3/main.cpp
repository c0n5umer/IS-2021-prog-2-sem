#include <iostream>
#include <vector>
#include "cbuffer.h"
#include "myAlgorithms.h"
#include "woman.h"

int main() {

    //test for CBuffer
    /*
    CBuffer<int> z(5);
    CBuffer<int> x(3);

    z.push_back(6);
    z.push_back(1);
    z.push_front(5);
    z.push_front(4);
    z.push_front(3);

    std::sort(z.begin(), z.end());
    for (int i = 0; i < z.size(); i++)
        std::cout << z[i] << " ";
    std::cout << "\n";

    z.pop_front();
    z.push_front(6);
    z.change_capacity(6);
    z.push_back(2);

    for (int i = 0; i < z.size(); i++)
        std::cout << z[i] << " ";
    std::cout << "\n";


    for (int i = 3; i > 0; i--)
        x.push_back(i);

    for (int i = 0; i < x.size(); i++)
        std::cout << x[i] << " ";
    std::cout << "\n";

    std::sort(x.begin(), x.end());

    for (int i = 0; i < x.size(); i++)
        std::cout << x[i] << " ";
    std::cout << "\n";


    if (all_of(x.begin(), x.end(), [](int x){return x > 0 && x < 4;}))
        std::cout << "All numbers are >0 and <4\n";
    */

    
    //test for algorithms
    /*
    std::vector<int> numbers;
    numbers.push_back(3);
    numbers.push_back(5);
    numbers.push_back(3);
    if (orlov::all_of(numbers.begin(), numbers.end(), [](int i) { return i % 2; }))
        std::cout << "All the elements are odd numbers.\n";
    if (orlov::is_palindrome(numbers.begin(), numbers.end(), [](int i, int j) { return i % 2 && j % 2; }))
        std::cout << "Odd palindrome\n";

    Woman w1(160, 1, 1), w2(150, 2, 2), w3(170, 3, 3);
    std::vector<Woman> women;
    women.push_back(w1);
    women.push_back(w2);
    women.push_back(w3);

    if (orlov::all_of(women.begin(), women.end(), [](Woman i) { return i.getBoobs() > 0; }))
        std::cout << "Everyone has boobs.\n";
    */
    return 0;
}
