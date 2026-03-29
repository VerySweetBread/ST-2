// Copyright 2026 UNN-CS
#ifndef INCLUDE_TASKS_H_
#define INCLUDE_TASKS_H_

#include <utility>

std::pair<double, double> poolCosts(double poolRadius = 3.0,
                                    double pathWidth = 1.0,
                                    double concreteCostPerSquareMeter = 1000.0,
                                    double fenceCostPerMeter = 2000.0);

double earthRopeGap(double earthRadiusKilometers = 6378.1,
                    double extraRopeLengthMeters = 1.0);

#endif  // INCLUDE_TASKS_H_
