//
// Created by Aleksandr Orlov on 10.04.2022.
//

#ifndef LAB3_WOMAN_H
#define LAB3_WOMAN_H

class Woman {
public:
    Woman(size_t height, size_t titties, size_t ass) {
        height_ = height;
        titties_ = titties;
        ass_ = ass;
    }

    size_t getBoobs() const {
        return titties_;
    }

    size_t getAss() const {
        return ass_;
    }

    bool operator==(const Woman &w) const {
        if (w.ass_ == ass_ && w.height_ == height_ && w.titties_ == titties_)
            return true;
        return false;
    }

    bool operator!=(const Woman &w) const {
        if (*this == w)
            return false;
        return true;
    }

    bool operator<(const Woman &w) const {
        if (titties_ + ass_ < w.titties_ + w.ass_)
            return true;
        return false;
    }

    bool operator>(const Woman &w) const {
        if (titties_ + ass_ > w.titties_ + w.ass_)
            return true;
        return false;
    }

    bool operator<=(const Woman &w) const {
        if (*this < w || *this == w)
            return true;
        return false;
    }

    bool operator>=(const Woman &w) const {
        if (*this > w || *this == w)
            return true;
        return false;
    }

private:
    size_t height_, titties_, ass_;
};

#endif //LAB3_WOMAN_H
