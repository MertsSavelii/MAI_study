#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"
#include <iostream>
#include "point.h"


class Triangle : public Figure {
public:
    Triangle();
    Triangle(double a, double b, double c);
    Triangle(std::istream &is);
    Triangle(const Triangle& other);

    virtual ~Triangle();

    size_t VertexesNumber();
    void Print(std::ostream& os);
    double Area();

private:
    double len_a, len_b, len_c;
};

#endif
