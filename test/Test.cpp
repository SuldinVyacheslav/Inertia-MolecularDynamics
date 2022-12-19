// Copyright 2022 Suldin Vyacheslav

#include <gtest/gtest.h>

#include "Physics.h"

using std::pair;
using std::vector;


#define EPS 0.00001

bool d_eq(double A, double B) {
  return (fabs(A - B) < EPS);
}

bool Vector_eq(Vector v, Vector u) { return d_eq(v.x, u.x) && d_eq(v.y, u.y) && d_eq(v.z, u.z); }

TEST(Laws, kinetic) {
  vector<Molecule> molecules;
  molecules.reserve(NUMBER_OF_MOLECULES);
  setup_positions(&molecules);

  int step = 0;
  double initial_kinetic = 0;

  for (int i = 0; i < molecules.size(); i++) {
    initial_kinetic += molecules[i].velocity.length();
  }
  double max = initial_kinetic;
  double min = initial_kinetic;
  while (step++ != 10000) {
    calc_force(&molecules);

    for (int i = 0; i < molecules.size(); i++) {
      molecules[i].semi_step();
    }

    double velocity = 0;
    for (int i = 0; i < molecules.size(); i++) {
      velocity += molecules[i].velocity.length();
    }
    if (max < velocity) {
      max = velocity;
    }
    if (min > velocity) {
      min = velocity;
    }

    EXPECT_TRUE(min > initial_kinetic * 0.8);
    EXPECT_TRUE(max < initial_kinetic * 1.2);
  }
}

TEST(Inertia, center) {
  vector<Molecule> molecules{Molecule(null(), null()),
                             Molecule(Vector(3, 3, 3), null()),
                             Molecule(Vector(-5, 4, 2), null())};

  Vector center = calc_inertia_center(molecules);
  EXPECT_TRUE(Vector_eq(center, Vector(-2, 7, 5) / 3));
}

TEST(Inertia, force) {
  vector<Molecule> molecules{Molecule(Vector(1, 1, -1), null()),
                             Molecule(Vector(3, 3, 3), null()),
                             Molecule(Vector(-5, 4, 2), null())};

  Vector prev_center = null();
  Vector center = calc_inertia_center(molecules);

  molecules[0].force = Delta(null(), Vector(2, 2, 2));
  molecules[1].force = Delta(null(), Vector(0, 1, 4));
  molecules[2].force = Delta(null(), Vector(1, 4, -1));
  calc_iner_force(&molecules, Delta(prev_center, center));
  EXPECT_TRUE(Vector_eq(molecules[2].iner_force.cur,
                        Vector(-0.596285, -0.596285, -2.98142)));
}