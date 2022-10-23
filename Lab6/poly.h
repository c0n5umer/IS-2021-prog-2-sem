//
// Created by Aleksandr Orlov on 24.05.2022.
//

#ifndef LAB6_POLY_H
#define LAB6_POLY_H

template<int... nums>
class Polynom {
private:
    static constexpr int coefs[] = {nums...};

    constexpr int pow(int a, int n) {
        int res = 1;

        while (n) {
            if (n & 1)
                res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }

public:
    constexpr int getValue(int x) {
        int res = 0;

        for (int i = 0; i < sizeof(coefs) / sizeof(int); ++i)
            res += pow(x, i) * coefs[i];

        return res;
    }

    friend std::ostream& operator<< (std::ostream &out, const Polynom &poly) {
        for (int i = 0; i < sizeof(coefs) / sizeof(int); ++i) {
            if (i == 0)
                out << coefs[0] << " ";
            else {
                out << "+ " << coefs[i] << "*x^" << i << " ";
            }
        }
        return out;
    }
};

#endif //LAB6_POLY_H
