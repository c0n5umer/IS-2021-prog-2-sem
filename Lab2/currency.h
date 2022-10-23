//
// Created by Aleksandr Orlov on 17.03.2022.
//

#ifndef LAB2_CURRENCY_H
#define LAB2_CURRENCY_H

#include <string>
#include <vector>


class Currency {
public:
    Currency();
    Currency(std::string charcode, std::string name, double value, int nominal);
    std::string getCharcode();
    std::string getName();
    double getValue();
    double getAverage();
    double getMedian();
    void updateValue(double value);
private:
    std::string charcode_;
    std::string name_;
    double value_;
    double sum_ = 0;
    int requests_ = 0;
    std::vector<double> values_;
};


#endif //LAB2_CURRENCY_H
