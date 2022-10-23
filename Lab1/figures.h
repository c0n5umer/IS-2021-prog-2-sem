//
// Created by Aleksandr Orlov on 22.02.2022.
//

#ifndef LAB1_1_FIGURES_H
#define LAB1_1_FIGURES_H

#include <vector>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <limits>

class Point {
public:
    Point(int x = 0, int y = 0);
    Point(Point const &p);

    Point& operator=(Point const &p);
    bool operator==(Point const &p) const;
    bool operator!=(Point const &p) const;

    int x() const;
    int y() const;
private:
    int x_;
    int y_;
};

class Polyline {
public:
    Polyline(std::vector<Point> vec = {Point(0, 0), Point(0, 0)});
    Polyline(Polyline const &p);

    Polyline& operator=(Polyline const &p);

    double perimeter() const;

    int points() const;
protected:
    std::vector<Point> vec_;
};

class ClosedPolyline : public Polyline {
public:
    ClosedPolyline();
    ClosedPolyline(std::vector<Point> vec);
    ClosedPolyline(ClosedPolyline const &p);
};

class Polygon {
public:
    Polygon();
    Polygon(std::vector<Point> vec);
    Polygon(Polygon const &p);

    Polygon& operator=(Polygon const &p);

    double perimeter() const;
    double square() const;
    int points() const;

protected:
    std::vector<Point> vec_;
    bool init = false;
};

class Triangle : public Polygon {
public:
    Triangle();
    Triangle(std::vector<Point> vec);
    Triangle(Triangle const &t);
};

class Trapezoid : public Polygon {
public:
    Trapezoid();
    Trapezoid(std::vector<Point> vec);
    Trapezoid(Trapezoid const &t);
};

class RegularPolygon : public  Polygon {
public:
    RegularPolygon();
    RegularPolygon(std::vector<Point> vec);
    RegularPolygon(RegularPolygon const &p);
};

bool intersect (Point a, Point b, Point c, Point d);

#endif //LAB1_1_FIGURES_H
