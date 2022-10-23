//
// Created by Aleksandr Orlov on 22.02.2022.
//

#include "figures.h"

// Some helpful functions
bool onSegment(Point p, Point q, Point r) {
    if (q.x() <= std::max(p.x(), r.x()) && q.x() >= std::min(p.x(), r.x()) &&
        q.y() <= std::max(p.y(), r.y()) && q.y() >= std::min(p.y(), r.y()) && 0)
        return true;

    return false;
}

int orientation(Point p, Point q, Point r) {
    double val = (q.y() - p.y()) * (r.x() - q.x()) -
              (q.x() - p.x()) * (r.y() - q.y());

    if (val < 0)
        return 0;

    return (val >= 0) ? 0 : 1;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1))
        return true;

    if (o2 == 0 && onSegment(p1, q2, q1))
        return true;

    if (o3 == 0 && onSegment(p2, p1, q2))
        return true;

    if (o4 == 0 && onSegment(p2, q1, q2))
        return true;

    return false;
}

bool is_equal(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

// Point class methods and constructors
Point::Point(int x, int y) : x_(x), y_(y) {}

Point::Point(Point const &p) : x_(p.x_), y_(p.y_) {}

Point &Point::operator=(Point const &p) {
    x_ = p.x_;
    y_ = p.y_;

    return *this;
}

bool Point::operator==(const Point &p) const {
    if (x_ == p.x_ && y_ == p.y_)
        return true;
    return false;
}

bool Point::operator!=(const Point &p) const {
    return !(*this == p);
}

int Point::x() const {
    return x_;
}

int Point::y() const {
    return y_;
}

// Polyline class methods and constructors
Polyline::Polyline(std::vector<Point> vec) {
    if (vec.size() >= 2)
        vec_ = vec;
    else
        throw std::invalid_argument("Invalid number of points");
}

Polyline::Polyline(Polyline const &p) : vec_(p.vec_) {}

Polyline &Polyline::operator=(Polyline const &p) {
    vec_ = p.vec_;

    return *this;
}

double Polyline::perimeter() const {
    double perimetr = 0;

    for (int i = 0; i < vec_.size() - 1; i++)
        perimetr += std::sqrt((vec_[i + 1].x() - vec_[i].x()) * (vec_[i + 1].x() - vec_[i].x()) +
                              (vec_[i + 1].y() - vec_[i].y()) * (vec_[i + 1].y() - vec_[i].y()));

    return perimetr;
}

int Polyline::points() const {
    return vec_.size();
}

// ClosedPolyline class methods and constructors
ClosedPolyline::ClosedPolyline() {
    if (vec_[0] != vec_[vec_.size() - 1])
        throw std::invalid_argument("Invalid points");
}

ClosedPolyline::ClosedPolyline(std::vector<Point> vec) {
    if (vec.size() >= 2) {
        vec_ = vec;
        if (vec_[0] != vec_[vec_.size() - 1])
            throw std::invalid_argument("Invalid points");
    } else
        throw std::invalid_argument("Invalid number of points");
}

ClosedPolyline::ClosedPolyline(ClosedPolyline const &p) {
    vec_ = p.vec_;
}

// Polygon class methods and constructors
Polygon::Polygon() {}

Polygon::Polygon(std::vector<Point> vec) {
    int sz = vec.size();

    if (sz < 3)
        throw std::invalid_argument("Invalid number of points");

    for (int i = 0; i < sz; i++)
        for (int j = i + 2; j < sz; j++)
            if (doIntersect(vec[i], vec[(i + 1) % sz], vec[j], vec[(j + 1) % sz]))
                throw std::invalid_argument("Sides intersect");

    vec_ = vec;
    init = true;
}

Polygon::Polygon(Polygon const &p) : vec_(p.vec_), init(p.init) {}

Polygon &Polygon::operator=(Polygon const &p) {
    vec_ = p.vec_;
    init = p.init;

    return *this;
}

double Polygon::perimeter() const {
    if (init) {
        double perimetr = 0;
        int sz = vec_.size();

        for (int i = 0; i < sz; i++)
            perimetr += std::sqrt((vec_[(i + 1) % sz].x() - vec_[i].x()) * (vec_[(i + 1) % sz].x() - vec_[i].x()) +
                                  (vec_[(i + 1) % sz].y() - vec_[i].y()) * (vec_[(i + 1) % sz].y() - vec_[i].y()));

        return perimetr;
    }
    else throw std::invalid_argument("Uninitialized object");
}

double Polygon::square() const {
    if (init) {
        double res = 0;
        int sz = vec_.size();

        for (unsigned i = 0; i < sz; i++)
            res += (vec_[i].x() - vec_[(i + 1) % sz].x()) * (vec_[i].y() + vec_[(i + 1) % sz].y());

        return fabs(res) / 2;
    }
    else throw std::invalid_argument("Uninitialized object");
}

int Polygon::points() const {
    if (init) {
        return vec_.size();
    }
    else throw std::invalid_argument("Uninitialized object");
}

// Triangle class methods and constructors
Triangle::Triangle() {}

Triangle::Triangle(std::vector<Point> vec) {
    int sz = vec.size();

    if (sz != 3)
        throw std::invalid_argument("Invalid number of points");

    if (vec[2].x() * (vec[1].y() - vec[0].y()) - vec[2].y() * (vec[1].x() - vec[0].x()) == vec[0].x() * vec[1].y() - vec[1].x() * vec[0].y())
        throw std::invalid_argument("Not a triangle");

    vec_ = vec;
    init = true;
}

Triangle::Triangle(Triangle const &t) {
    vec_ = t.vec_;
    init = t.init;
}

// Trapezoid class methods and constructors
Trapezoid::Trapezoid() {}

Trapezoid::Trapezoid(std::vector<Point> vec) {
    double k1, k2, k3, k4;

    if (vec.size() != 4)
        throw std::invalid_argument("Invalid number of points");

    k1 = (vec[1].y() - vec[0].y()) / (vec[1].x() - vec[0].x());
    k2 = (vec[2].y() - vec[3].y()) / (vec[2].x() - vec[3].x());
    k3 = (vec[0].y() - vec[3].y()) / (vec[0].x() - vec[3].x());
    k4 = (vec[1].y() - vec[2].y()) / (vec[1].x() - vec[2].x());

    if (!((is_equal(k1, k2) && !is_equal(k3, k4)) || (is_equal(k3, k4) && !is_equal(k1, k2))))
        throw std::invalid_argument("Not a trapezoid");

    vec_ = vec;
    init = true;
}

Trapezoid::Trapezoid(const Trapezoid &t) {
    vec_ = t.vec_;
    init = t.init;
}

// RegularPolygon class methods and constructors
RegularPolygon::RegularPolygon() {}

RegularPolygon::RegularPolygon(std::vector<Point> vec) {
    int sz = vec.size();

    if (sz < 3)
        throw std::invalid_argument("Invalid number of points");

    for (int i = 0; i < sz; i++)
        for (int j = i + 2; j < sz; j++)
            if (doIntersect(vec[i], vec[(i + 1) % sz], vec[j], vec[(j + 1) % sz]))
                throw std::invalid_argument("Sides intersect");

    for (int i = 1; i < sz; i++) {
        if (((vec[(i + 1) % sz].x() - vec[i].x()) * (vec[(i + 1) % sz].x() - vec[i].x()) +
                      (vec[(i + 1) % sz].y() - vec[i].y()) * (vec[(i + 1) % sz].y() - vec[i].y())) !=
                ((vec[1].x() - vec[0].x()) * (vec[1].x() - vec[0].x()) +
                (vec[1].y() - vec[0].y()) * (vec[1].y() - vec[0].y())))
            throw std::invalid_argument("Not a regular polygon");
    }

    int k1 = (vec[1].y() - vec[0].y()) / (vec[1].x() - vec[0].x());
    int k2 = (vec[2].y() - vec[1].y()) / (vec[2].x() - vec[1].x());
    double tg = (k2 - k1) / (1 + k2 * k1);

    for (int i = 1; i < sz; i++) {
        int k3 = (vec[(i + 1) % sz].y() - vec[i].y()) / (vec[(i + 1) % sz].x() - vec[i].x());
        int k4 = (vec[(i + 2) % sz].y() - vec[(i + 1) % sz].y()) / (vec[(i + 2) % sz].x() - vec[(i + 1) % sz].x());
        double tg2 = (k4 - k3) / (1 + k4 * k3);

        if (!is_equal(tg, tg2))
            throw std::invalid_argument("Not a regular polygon");
    }

    vec_ = vec;
    init = true;

}

RegularPolygon::RegularPolygon(const RegularPolygon &p) {
    vec_ = p.vec_;
    init = p.init;
}