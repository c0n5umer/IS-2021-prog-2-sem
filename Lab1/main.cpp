#include <iostream>
#include "figures.h"
#include "polynomial.h"

int main() {

    std::vector<Point> kv = {Point(0, 0), Point(0, 2), Point(2, 2), Point(2, 0)}; // квадрат
    std::vector<Point> tr = {Point(0, 0), Point(0, 1), Point(1, 0)}; // треугольник
    std::vector<Point> trap = {Point(1, 2), Point(3, 2), Point(3, 0), Point(0, 0)}; // трапеция
    std::vector<Point> romb = {Point(1, 4), Point(2, 2), Point(1, 0), Point(0, 2)}; //ромб



   try {
        RegularPolygon rp(kv);
        Triangle  t(tr);
        Trapezoid tp(trap);
        Polygon rb(romb);

        std::cout << rp.square() << " " << t.square() << " " << tp.square() << " " << rb.square() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "you are stupid because " << e.what() << std::endl;
    }



   std::vector <double> mp = {2.6, 3.2};
   std::vector <double> mp2 = {3.1};

   Polynomial po(mp);
   Polynomial p2(mp2), p3(p2);
   p3 = p2 * po;
   p2 *= 1.5;
   std::cout << p3 << std::endl << p2;

   return 0;
}
