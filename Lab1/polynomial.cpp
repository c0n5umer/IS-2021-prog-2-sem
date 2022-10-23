//
// Created by Aleksandr Orlov on 03.03.2022.
//

#include "polynomial.h"

Polynomial::Polynomial() {}

Polynomial::Polynomial(std::vector <double> poly) {
    if (!poly.empty()) {
        poly_ = poly;
        init = true;
    }
}

Polynomial::Polynomial(const Polynomial &p): poly_(p.poly_), init(p.init) {}

Polynomial &Polynomial::operator=(const Polynomial &p) {
    poly_ = p.poly_;
    init = p.init;

    return *this;
}

bool Polynomial::operator==(const Polynomial &p) const {
    if (init == p.init && poly_ == p.poly_)
        return true;
    return false;
}

bool Polynomial::operator!=(const Polynomial &p) const {
    return !(*this == p);
}

void Polynomial::operator-() {
   for (int i = 0; i < poly_.size(); i++)
       poly_[i] *= -1;
}

void Polynomial::cutZero() {
    for (int i = poly_.size() - 1; i >= 0; i--) {
        if (poly_[i] != 0)
            break;
        poly_.pop_back();
    }
}

Polynomial Polynomial::operator-(const Polynomial &p) {
    std::vector<double> tmp(std::max(this->poly_.size(), p.poly_.size()), 0);

    for (int i = 0; i < this->poly_.size(); i++)
        tmp[i] += this->poly_[i];

    for (int i = 0; i < p.poly_.size(); i++)
        tmp[i] -= p.poly_[i];

    Polynomial temp(tmp);
    temp.cutZero();

    return temp;
}

Polynomial Polynomial::operator+(const Polynomial &p) {
    Polynomial left(*this), right(p);

    -right;
    left = left - right;
    left.cutZero();

    return left;
}

Polynomial Polynomial::operator+=(const Polynomial &p) {
    *this = *this + p;
    this->cutZero();

    return *this;
}

Polynomial Polynomial::operator-=(const Polynomial &p) {
    *this = *this - p;
    this->cutZero();

    return *this;
}

Polynomial Polynomial::operator*(const Polynomial &p) {
    Polynomial temp;

    temp.poly_.resize(this->poly_.size() + p.poly_.size() + 1);
    for (int i = 0; i < this->poly_.size(); i++)
        for (int j = 0; j < p.poly_.size(); j++)
            temp.poly_[i + j] += this->poly_[i] * p.poly_[j];

    temp.cutZero();
    temp.init = true;

    return temp;
}

Polynomial Polynomial::operator*=(const Polynomial &p) {
    *this = *this * p;

    this->cutZero();

    return *this;
}

Polynomial Polynomial::operator*=(double num) {
    for (int i = 0; i < this->poly_.size(); i++)
        this->poly_[i] *= num;

    this->cutZero();

    return *this;
}

Polynomial Polynomial::operator*(double num) {
    *this *= num;

    this->cutZero();

    return *this;
}

Polynomial Polynomial::operator/(double num) {
    for (int i = 0; i < this->poly_.size(); i++)
        this->poly_[i] /= num;

    this->cutZero();

    return *this;
}

Polynomial Polynomial::operator/=(double num) {
    *this = *this / num;

    this->cutZero();

    return *this;
}

double Polynomial::operator[](int num) {
    if (num >= this->poly_.size())
        return 0;
    return this->poly_[num];
}