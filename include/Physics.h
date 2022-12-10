// Copyright 2022 Suldin Vyacheslav

#ifndef INCLUDE_PHYSICS_H_
#define INCLUDE_PHYSICS_H_

#include "Molecule.h"
#include <vector>

extern double maxwell(double V);
extern double get_maxwell_dist();
extern Vector get_maxwell_vector();
extern double lennard_jones(double d);
extern Vector calc_inertia_center(std::vector<Molecule> Molecules);
extern std::pair<double, Vector> calc_periodic_dist(Molecule tarMol,
                                                    Molecule copMol);
extern void calc_iner_force(std::vector<Molecule> *Molecules, Delta iner);
extern double calculateN(double Temp);

#endif
