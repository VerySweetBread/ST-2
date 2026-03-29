// Copyright 2026 UNN-CS
#include "tasks.h"

#include <stdexcept>
#include <utility>

#include "circle.h"

std::pair<double, double> poolCosts(double poolRadius,
                                    double pathWidth,
                                    double concreteCostPerSquareMeter,
                                    double fenceCostPerMeter) {
  if (poolRadius < 0.0 || pathWidth < 0.0 ||
      concreteCostPerSquareMeter < 0.0 || fenceCostPerMeter < 0.0) {
    throw std::invalid_argument("Pool task parameters must be non-negative");
  }

  Circle inner(poolRadius);
  Circle outer(poolRadius + pathWidth);

  const double concreteArea = outer.getArea() - inner.getArea();
  const double concreteCost = concreteArea * concreteCostPerSquareMeter;
  const double fenceCost = outer.getFerence() * fenceCostPerMeter;

  return {concreteCost, fenceCost};
}

double earthRopeGap(double earthRadiusKilometers,
                    double extraRopeLengthMeters) {
  if (earthRadiusKilometers < 0.0 || extraRopeLengthMeters < 0.0) {
    throw std::invalid_argument("Rope task parameters must be non-negative");
  }

  Circle earth(earthRadiusKilometers * 1000.0);
  Circle enlarged(earth.getRadius());
  enlarged.setFerence(earth.getFerence() + extraRopeLengthMeters);

  return enlarged.getRadius() - earth.getRadius();
}
