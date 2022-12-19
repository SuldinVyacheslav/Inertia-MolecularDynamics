// Copyright 2022 Suldin Vyacheslav

#ifndef INCLUDE_PHYSICS_H_
#define INCLUDE_PHYSICS_H_

#include <utility>
#include <vector>

#include "Molecule.h"

extern void setup_positions(std::vector<Molecule> *molecules);
extern double maxwell(double V);
extern double get_maxwell_dist();
extern Vector get_maxwell_vector();
extern double lennard_jones(double d);
extern void calc_force(std::vector<Molecule> *molecules);
extern Vector calc_inertia_center(const std::vector<Molecule> &Molecules);
extern std::pair<double, Vector> calc_periodic_dist(Molecule tarMol,
                                                    Molecule copMol);
extern void calc_iner_force(std::vector<Molecule> *Molecules, Delta iner);
extern double calculateN(double Temp);

#endif  // INCLUDE_PHYSICS_H_
