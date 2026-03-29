// Copyright 2022 UNN-CS
#include "circle.h"

#include <cmath>
#include <stdexcept>

Circle::Circle(double radius) {
  setRadius(radius);
}

double Circle::pi() {
  return 3.14159265358979323846;
}

void Circle::validateNonNegative(double value) {
  if (value < 0.0) {
    throw std::invalid_argument("Circle value must be non-negative");
  }
}

void Circle::updateFromRadius() {
  ference_ = 2.0 * pi() * radius_;
  area_ = pi() * radius_ * radius_;
}

void Circle::setRadius(double radius) {
  validateNonNegative(radius);
  radius_ = radius;
  updateFromRadius();
}

void Circle::setFerence(double ference) {
  validateNonNegative(ference);
  radius_ = ference / (2.0 * pi());
  updateFromRadius();
}

void Circle::setArea(double area) {
  validateNonNegative(area);
  area_ = area;
  radius_ = std::sqrt(area_ / pi());
  ference_ = 2.0 * pi() * radius_;
}

double Circle::getRadius() const {
  return radius_;
}

double Circle::getFerence() const {
  return ference_;
}

double Circle::getArea() const {
  return area_;
}
