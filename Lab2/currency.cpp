//
// Created by Aleksandr Orlov on 17.03.2022.
//

#include "currency.h"

Currency::Currency() {}

Currency::Currency(std::string charcode, std::string name, double value, int nominal) {
    charcode_ = charcode;
    name_ = name;
    value_ = value / nominal;
    sum_ += value_;
    ++requests_;
    values_.push_back(value_);
}

std::string Currency::getCharcode() {
    return charcode_;
}

std::string Currency::getName() {
    return name_;
}

double Currency::getValue() {
    return value_;
}

double Currency::getAverage() {
    if (requests_ < 1)
        return 0;

    return sum_ / requests_;
}

double Currency::getMedian() {
    std::sort(values_.begin(), values_.end());

    if (values_.size() < 2)
        return 0;

    if (values_.size() % 2 != 0)
        return values_[values_.size() / 2];
    else
        return (values_[values_.size() / 2 - 1] + values_[values_.size() / 2]) / 2;
}

void Currency::updateValue(double value) {
    value_ = value;
    sum_ += value;
    ++requests_;
    values_.push_back(value);
}