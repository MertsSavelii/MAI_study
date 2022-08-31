#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <iostream>

class Point {
public:
  Point();
  Point(double x, double y);
  
  double getX() const;
  double getY() const;
  
  friend std::istream& operator>>(std::istream& is, Point& p);
  friend std::ostream& operator<<(std::ostream& os, const Point& p);
  const Point& operator=(const Point& other);
  bool operator!=(const Point& other) const;
  bool operator==(const Point& other) const;
private:
  double x_;
  double y_;
};

#endif

Point::Point() : x_(0.0), y_(0.0) {}

Point::Point(double x, double y) : x_(x), y_(y) {}

double Point::getX() const{
  	return x_;
}

double Point::getY() const{
  	return y_;
}

std::istream& operator>>(std::istream& is, Point& p) {
  	is >> p.x_ >> p.y_;
  	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
  	os << "(" << p.x_ << ", " << p.y_ << ")";
  	return os;
}

const Point& Point::operator=(const Point& other) {
	if (this == &other)
    	return *this;
	x_ = other.x_;
	y_ = other.y_;
  	return *this;
}

bool Point::operator!=(const Point& other) const{
	if (x_ == other.x_) return false;
	if (y_ == other.y_) return false;
 	return true;
}

bool Point::operator==(const Point& other) const{
  	if (x_ != other.x_) return false;
  	if (y_ != other.y_) return false;
  	return true;
}