// Copyright 2022 Suldin Vyacheslav

#include "Molecule.h"

#include <vector>

Delta::Delta(Vector prev, Vector cur) : prev(prev), cur(cur) {}

Delta::Delta() {
  prev = null();
  cur = null();
}

Molecule::Molecule(Vector coor, Vector vel)
    : coordinates(Delta(null(), coor)),
      velocity(vel),
      force(Delta(null(), null())) {
  mass = ARGON_MASS;
  radius = ARGON_RADIUS;
}

void Molecule::semi_step() {
  coordinates.prev = coordinates.cur;

  Vector acc = force.prev / mass;

  coordinates.cur += (velocity * DELTA_T) + acc * (pow(DELTA_T, 2) / 2);

  Vector semi_vel = velocity + acc * (DELTA_T / 2);

  acc = force.cur / mass;

  velocity = semi_vel + acc * (DELTA_T / 2);

  periodic();
}

void Molecule::verlet() {
  coordinates.prev = coordinates.cur;

  Vector acc = force.prev / mass;

  coordinates.cur += (velocity * DELTA_T) + acc * (pow(DELTA_T, 2) / 2);

  Vector accN = force.cur / mass;

  velocity += (acc + accN) * (DELTA_T / 2);

  periodic();
}

void Molecule::base() {
  coordinates.prev = coordinates.cur;

  coordinates.cur += velocity * DELTA_T;

  velocity += (force.cur / mass) * DELTA_T;

  periodic();
}

void Check(double *cor) {
  if (*cor >= SIDE_OF_SYSTEM || *cor <= 0) {
    *cor += (*cor <= 0 ? 1 : -1) * SIDE_OF_SYSTEM;
  }
}

void Molecule::periodic() {
  Check(&coordinates.cur.x);
  Check(&coordinates.cur.y);
  Check(&coordinates.cur.z);
}

void Molecule::set_iner(const Vector &iner_force) {
  this->iner_force.cur = iner_force;
}

