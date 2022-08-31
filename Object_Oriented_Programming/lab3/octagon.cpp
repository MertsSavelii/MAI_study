#include "octagon.h"

#include <cmath>

Octagon::Octagon()
    : a_(0, 0),
     b_(0, 0),
     c_(0, 0),
     d_(0, 0),
     e_(0, 0),
     f_(0, 0),
     g_(0, 0),
     h_(0, 0) {
  //std::cout << "Default octagon created" << std::endl;
}

Octagon::Octagon(Point a, Point b, Point c, Point d, Point e, Point f, Point g, Point h)
    : a_(a),
     b_(b),
     c_(c),
     d_(d),
     e_(e),
     f_(f),
     g_(g),
     h_(h) {
  //std::cout << "Octagon created" << std::endl;
}

Octagon::Octagon(std::istream &is) { 
    is >> a_ >> b_ >> c_ >> d_ >> e_ >> f_ >> g_ >> h_;
  //std::cout << "Octagon created via istream" << std::endl;
}

Octagon::Octagon(const Octagon& other)
    : Octagon(other.a_, other.b_, other.c_, other.d_, other.e_, other.f_,
              other.g_, other.h_) {
  //std::cout << "Made copy of octagon" << std::endl; 

}

size_t Octagon::VertexesNumber() {
    return 8;
}

void Octagon::Print(std::ostream& os) {
    os << "Octagon: ";
    os <<  a_ << " ";
    os <<  b_ << " ";
    os <<  c_ << " ";
    os <<  d_ << " ";
    os <<  e_ << " ";
    os <<  f_ << " ";
    os <<  g_ << " ";
    os <<  h_ << " ";
    os << std::endl;
}

double Octagon::Area() {
    return 0.5 * abs( a_.getX()*b_.getY() + b_.getX()*c_.getY() + c_.getX()*d_.getY() + d_.getX()*e_.getY() + e_.getX()*f_.getY() + f_.getX()*g_.getY() + g_.getX()*h_.getY() + h_.getX()*a_.getY()
  	- a_.getY()*b_.getX() - b_.getY()*c_.getX() - c_.getY()*d_.getX() - d_.getY()*e_.getX() - e_.getY()*f_.getX() - f_.getY()*g_.getX() - g_.getY()*h_.getX() - h_.getY()*a_.getX());
}

Octagon::~Octagon() {
    //std::cout << "Octagon deleted" << std::endl;
}
