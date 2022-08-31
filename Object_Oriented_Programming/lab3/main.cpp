#include <iostream>
#include "triangle.h"
#include "square.h"
#include "octagon.h"
#include "point.h"


int main()
{
    std::cout << "Enter the points' coordinates of triangle:\n";
    Triangle a(std::cin);
    std::cout << "Triangle's number of vertexes: " << a.VertexesNumber() << "\n";
    std::cout << "Triangles's area: " << a.Area() << "\n";
    a.Print(std::cout);
    std::cout << std::endl;

    std::cout << "Enter the points' coordinates of square:\n";
    Square b(std::cin);
    std::cout << "Square's number of vertexes: " << b.VertexesNumber() << "\n";
    std::cout << "Square's area: " << b.Area() << "\n";
    b.Print(std::cout);
    std::cout << std::endl;

    std::cout << "Enter the points' coordinates of octagon:\n";
    Octagon c(std::cin);
    std::cout << "Octagon's number of vertexes: " << c.VertexesNumber() << "\n";
    std::cout << "Octagon's area: " << c.Area() << "\n";
    c.Print(std::cout);
    std::cout << std::endl;
    
    return 0;
}