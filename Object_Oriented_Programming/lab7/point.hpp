#ifndef POINT_H
#define POINT_H

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