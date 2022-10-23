//
// Created by Aleksandr Orlov on 03.03.2022.
//

#ifndef LAB1_1_POLYNOMIAL_H
#define LAB1_1_POLYNOMIAL_H

#include <vector>
#include <ostream>
#include <iostream>

class Polynomial {
public:
    Polynomial();
    Polynomial(std::vector <double> poly);
    Polynomial(Polynomial const &p);

    Polynomial& operator=(Polynomial const &p);
    bool operator==(Polynomial const &p) const;
    bool operator!=(Polynomial const &p) const;
    void cutZero();
    Polynomial operator-(const Polynomial &p);
    void operator-();
    Polynomial operator+(const Polynomial &p);
    Polynomial operator+=(const Polynomial &p);
    Polynomial operator-=(const Polynomial &p);
    Polynomial operator*(const Polynomial &p);
    Polynomial operator*=(const Polynomial &p);
    Polynomial operator*=(double num);
    Polynomial operator*(double num);
    Polynomial operator/(double num);
    Polynomial operator/=(double num);
    double operator[](int num);
    friend std::ostream& operator<<(std::ostream& out, const Polynomial &p) {
        if (p.init) {
            for (int i = 0; i < p.poly_.size(); i++) {
                if (i == 0) {
                    if (p.poly_[0] != 0)
                        out << p.poly_[0];
                }
                else
                    if (p.poly_[i] != 0) {
                        if (p.poly_[i] > 0)
                            out << "+" << p.poly_[i] << "x^" << i;
                        else
                            out << p.poly_[i] << "x^" << i;
                    }
            }
        }
        else
            out << 0;
        return out;
    }
    friend Polynomial& operator>>(std::istream& in, Polynomial &p) {
        double temp;

        p.poly_.clear();
        while (in >> temp)
            p.poly_.push_back(temp);
        p.cutZero();
        p.init = true;
        return p;
    }
private:
    std::vector <double> poly_;
    bool init = false;
};


#endif //LAB1_1_POLYNOMIAL_H
