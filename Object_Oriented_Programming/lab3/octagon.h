#ifndef OCTAGON_H
#define OCTAGON_H

#include <iostream>

#include "figure.h"
#include "point.h"


class Octagon : public Figure {
public:
    Octagon();
    Octagon(Point a, Point b, Point c, Point d, Point e, Point f, Point g, Point h);
    Octagon(std::istream &is);
    Octagon(const Octagon& other);

    virtual ~Octagon();

    size_t VertexesNumber();
    void Print(std::ostream& os);
    double Area();

private:
    Point a_, b_, c_, d_, e_, f_, g_, h_;
};

#endif
