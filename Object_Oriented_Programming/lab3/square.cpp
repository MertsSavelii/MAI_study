#include "square.h"

#include <cmath>

static Point a_, b_, c_, d_;

Square::Square()
    : len_ab(0.0),
      len_bc(0.0),
      len_cd(0.0),
      len_da(0.0) {
  //std::cout << "Default square created" << std::endl;
}

Square::Square(double a, double b, double c, double d)
    : len_ab(a),
      len_bc(b),
      len_cd(c),
      len_da(d) {
  //std::cout << "Square created" << std::endl;
}

Square::Square(std::istream &is) { 
    is >> a_ >> b_ >> c_ >> d_;
      len_ab = a_.dist(b_);
      len_bc = b_.dist(c_);
      len_cd = c_.dist(d_);
      len_da = d_.dist(a_);
  //std::cout << "Square created via istream" << std::endl;
}

Square::Square(const Square& other)
    : Square(other.len_ab, other.len_bc, other.len_cd, other.len_da) {
  //std::cout << "Made copy of square" << std::endl;

}

size_t Square::VertexesNumber() {
    return 4;
}

void Square::Print(std::ostream& os) {
    //std::ostream& os = std::cout;
    os << "Square: ";
    os <<  a_ << " ";
    os << b_ << " ";
    os << c_ << " ";
    os << d_ <<  " ";
    os << std::endl;
}

double Square::Area() {
    return len_ab * len_bc;
}

Square::~Square() {
    //std::cout << "Square deleted" << std::endl;
}
