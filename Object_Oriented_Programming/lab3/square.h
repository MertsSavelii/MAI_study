#ifndef SQUARE_H
#define SQUARE_H

#include "figure.h"
#include <iostream>
#include "point.h"


class Square : public Figure {
public:
    Square();
    Square(double a, double b, double c, double d);
    Square(std::istream &is);
    Square(const Square& other);

    virtual ~Square();

    size_t VertexesNumber();
    void Print(std::ostream& os);
    double Area();

private:
    double len_ab, len_bc, len_cd, len_da;
};

#endif