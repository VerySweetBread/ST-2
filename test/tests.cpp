// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <stdexcept>

#include "circle.h"
#include "tasks.h"

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kEps = 1e-9;
}  // namespace

TEST(CircleTest, ConstructorStoresRadius) {
  Circle circle(5.0);
  EXPECT_NEAR(5.0, circle.getRadius(), kEps);
}

TEST(CircleTest, ConstructorCalculatesFerence) {
  Circle circle(5.0);
  EXPECT_NEAR(10.0 * kPi, circle.getFerence(), kEps);
}

TEST(CircleTest, ConstructorCalculatesArea) {
  Circle circle(5.0);
  EXPECT_NEAR(25.0 * kPi, circle.getArea(), kEps);
}

TEST(CircleTest, ConstructorWithNegativeRadiusThrows) {
  EXPECT_THROW(Circle(-1.0), std::invalid_argument);
}

TEST(CircleTest, SetRadiusUpdatesRadius) {
  Circle circle(1.0);
  circle.setRadius(7.25);
  EXPECT_NEAR(7.25, circle.getRadius(), kEps);
}

TEST(CircleTest, SetRadiusUpdatesFerence) {
  Circle circle(1.0);
  circle.setRadius(7.25);
  EXPECT_NEAR(14.5 * kPi, circle.getFerence(), kEps);
}

TEST(CircleTest, SetRadiusUpdatesArea) {
  Circle circle(1.0);
  circle.setRadius(7.25);
  EXPECT_NEAR(7.25 * 7.25 * kPi, circle.getArea(), kEps);
}

TEST(CircleTest, SetRadiusToZeroResetsDependentValues) {
  Circle circle(3.0);
  circle.setRadius(0.0);
  EXPECT_NEAR(0.0, circle.getFerence(), kEps);
  EXPECT_NEAR(0.0, circle.getArea(), kEps);
}

TEST(CircleTest, SetRadiusWithNegativeValueThrows) {
  Circle circle(2.0);
  EXPECT_THROW(circle.setRadius(-0.5), std::invalid_argument);
}

TEST(CircleTest, SetFerenceUpdatesFerence) {
  Circle circle(1.0);
  circle.setFerence(20.0);
  EXPECT_NEAR(20.0, circle.getFerence(), kEps);
}

TEST(CircleTest, SetFerenceUpdatesRadius) {
  Circle circle(1.0);
  circle.setFerence(20.0);
  EXPECT_NEAR(10.0 / kPi, circle.getRadius(), kEps);
}

TEST(CircleTest, SetFerenceUpdatesArea) {
  Circle circle(1.0);
  circle.setFerence(20.0);
  EXPECT_NEAR(100.0 / kPi, circle.getArea(), kEps);
}

TEST(CircleTest, SetFerenceToZeroResetsCircle) {
  Circle circle(2.0);
  circle.setFerence(0.0);
  EXPECT_NEAR(0.0, circle.getRadius(), kEps);
  EXPECT_NEAR(0.0, circle.getArea(), kEps);
}

TEST(CircleTest, SetFerenceWithNegativeValueThrows) {
  Circle circle(2.0);
  EXPECT_THROW(circle.setFerence(-3.0), std::invalid_argument);
}

TEST(CircleTest, SetAreaUpdatesArea) {
  Circle circle(1.0);
  circle.setArea(81.0);
  EXPECT_NEAR(81.0, circle.getArea(), kEps);
}

TEST(CircleTest, SetAreaUpdatesRadius) {
  Circle circle(1.0);
  circle.setArea(81.0);
  EXPECT_NEAR(std::sqrt(81.0 / kPi), circle.getRadius(), kEps);
}

TEST(CircleTest, SetAreaUpdatesFerence) {
  Circle circle(1.0);
  circle.setArea(81.0);
  EXPECT_NEAR(2.0 * std::sqrt(81.0 * kPi), circle.getFerence(), kEps);
}

TEST(CircleTest, SetAreaToZeroResetsCircle) {
  Circle circle(2.0);
  circle.setArea(0.0);
  EXPECT_NEAR(0.0, circle.getRadius(), kEps);
  EXPECT_NEAR(0.0, circle.getFerence(), kEps);
}

TEST(CircleTest, SetAreaWithNegativeValueThrows) {
  Circle circle(2.0);
  EXPECT_THROW(circle.setArea(-8.0), std::invalid_argument);
}

TEST(CircleTest, SequentialUpdatesRemainConsistent) {
  Circle circle(4.0);
  circle.setFerence(18.0);
  circle.setArea(50.0);
  EXPECT_NEAR(std::sqrt(50.0 / kPi), circle.getRadius(), kEps);
  EXPECT_NEAR(50.0, circle.getArea(), kEps);
  EXPECT_NEAR(2.0 * kPi * circle.getRadius(), circle.getFerence(), kEps);
}

TEST(TasksTest, EarthRopeGapForDefaultValuesIsOneOverTwoPi) {
  EXPECT_NEAR(1.0 / (2.0 * kPi), earthRopeGap(), kEps);
}

TEST(TasksTest, EarthRopeGapDoesNotDependOnPlanetRadius) {
  EXPECT_NEAR(earthRopeGap(1.0, 1.0), earthRopeGap(6378.1, 1.0), kEps);
}

TEST(TasksTest, EarthRopeGapWithTwoExtraMetersDoublesResult) {
  EXPECT_NEAR(1.0 / kPi, earthRopeGap(6378.1, 2.0), kEps);
}

TEST(TasksTest, EarthRopeGapWithNegativeRadiusThrows) {
  EXPECT_THROW(earthRopeGap(-1.0, 1.0), std::invalid_argument);
}

TEST(TasksTest, EarthRopeGapWithNegativeExtraLengthThrows) {
  EXPECT_THROW(earthRopeGap(6378.1, -1.0), std::invalid_argument);
}

TEST(TasksTest, PoolCostsDefaultConcreteCostIsCorrect) {
  const auto [concreteCost, fenceCost] = poolCosts();
  EXPECT_NEAR(7000.0 * kPi, concreteCost, kEps);
  EXPECT_GT(fenceCost, 0.0);
}

TEST(TasksTest, PoolCostsDefaultFenceCostIsCorrect) {
  const auto [concreteCost, fenceCost] = poolCosts();
  EXPECT_GT(concreteCost, 0.0);
  EXPECT_NEAR(16000.0 * kPi, fenceCost, kEps);
}

TEST(TasksTest, PoolCostsWithCustomValuesAreCorrect) {
  const auto [concreteCost, fenceCost] = poolCosts(2.0, 2.0, 10.0, 20.0);
  EXPECT_NEAR(120.0 * kPi, concreteCost, kEps);
  EXPECT_NEAR(160.0 * kPi, fenceCost, kEps);
}

TEST(TasksTest, PoolCostsWithoutPathUsePoolBoundaryForFence) {
  const auto [concreteCost, fenceCost] = poolCosts(3.0, 0.0, 1000.0, 2000.0);
  EXPECT_NEAR(0.0, concreteCost, kEps);
  EXPECT_NEAR(12000.0 * kPi, fenceCost, kEps);
}

TEST(TasksTest, PoolCostsWithNegativeRadiusThrows) {
  EXPECT_THROW(poolCosts(-3.0, 1.0, 1000.0, 2000.0), std::invalid_argument);
}

TEST(TasksTest, PoolCostsWithNegativePathWidthThrows) {
  EXPECT_THROW(poolCosts(3.0, -1.0, 1000.0, 2000.0), std::invalid_argument);
}

TEST(TasksTest, PoolCostsWithNegativeConcreteCostThrows) {
  EXPECT_THROW(poolCosts(3.0, 1.0, -1000.0, 2000.0), std::invalid_argument);
}

TEST(TasksTest, PoolCostsWithNegativeFenceCostThrows) {
  EXPECT_THROW(poolCosts(3.0, 1.0, 1000.0, -2000.0), std::invalid_argument);
}
