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
}

std::istream& operator>>(std::istream& is, Octagon& obj) {
    is >> obj.a_;
	is >> obj.b_;
	is >> obj.c_;
	is >> obj.d_;
	is >> obj.e_;
	is >> obj.f_;
	is >> obj.g_;
	is >> obj.h_;
  	return is;
}

size_t Octagon::VertexesNumber() {
    return 8;
}

std::ostream& operator<<(std::ostream& os, const Octagon& obj) {
    os << "Octagon: ";
    os <<  obj.a_ << " ";
    os <<  obj.b_ << " ";
    os <<  obj.c_ << " ";
    os <<  obj.d_ << " ";
    os <<  obj.e_ << " ";
    os <<  obj.f_ << " ";
    os <<  obj.g_ << " ";
    os <<  obj.h_ << " ";
    return os;
}

double Octagon::Area() const{
  	return 0.5 * abs( a_.getX()*b_.getY() + b_.getX()*c_.getY() + c_.getX()*d_.getY() + d_.getX()*e_.getY() + e_.getX()*f_.getY() + f_.getX()*g_.getY() + g_.getX()*h_.getY() + h_.getX()*a_.getY()
  	- a_.getY()*b_.getX() - b_.getY()*c_.getX() - c_.getY()*d_.getX() - d_.getY()*e_.getX() - e_.getY()*f_.getX() - f_.getY()*g_.getX() - g_.getY()*h_.getX() - h_.getY()*a_.getX());
}

const Octagon& Octagon::operator=(const Octagon& other) {
  	if (this == &other)
    	return *this;

  	a_ = other.a_;
  	b_ = other.b_;
  	c_ = other.c_;
  	d_ = other.d_;
  	e_ = other.e_;
  	f_ = other.f_;
  	g_ = other.g_;
  	h_ = other.h_;

  	return *this;
}

bool Octagon::operator==(const Octagon& other) const{
    if (a_ != other.a_) return false;
    if (b_ != other.b_) return false;
    if (c_ != other.c_) return false;
    if (d_ != other.d_) return false;
    if (e_ != other.e_) return false;
    if (f_ != other.f_) return false;
    if (g_ != other.g_) return false;
    if (h_ != other.h_) return false;

    return true;
}
bool Octagon::operator!=(const Octagon& other) const{
    if (a_ != other.a_) return true;
    if (b_ != other.b_) return true;
    if (c_ != other.c_) return true;
    if (d_ != other.d_) return true;
    if (e_ != other.e_) return true;
    if (f_ != other.f_) return true;
    if (g_ != other.g_) return true;
    if (h_ != other.h_) return true;

    return false;
}

Octagon::~Octagon() {
}