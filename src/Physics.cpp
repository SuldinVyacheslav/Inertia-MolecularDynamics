// Copyright 2022 Suldin Vyacheslav

#include "Physics.h"

double maxwell(double V) {
  double m = ARGON_MASS;
  int T = 300;
  double k = 1.38 * pow(10, -23);
  double A1 = (1 / sqrt(M_PI)) * sqrt(m / (2 * k * T));
  return A1 * exp(-((m * pow(V, 2)) / (2 * k * T)));
}

Vector get_maxwell_vector() {
  return Vector(get_maxwell_dist(), get_maxwell_dist(), get_maxwell_dist());
}

double get_maxwell_dist() {
  static unsigned int seed = time(NULL);
  double sum = 0;
  std::vector<double> vel;
  for (int i = 0; i < 1000; i++) {
    double prob = maxwell(i);
    vel.push_back(prob);
    sum += prob;
  }
  double b = rand_r(&seed) % 100;

  int i = 0;
  double cur = 0;

  for (i = 0; i < static_cast<int>(vel.size()) && b > cur * 100; i++) {
    cur += vel[i] / sum;
  }
  return (rand_r(&seed) % 2 == 0 ? -1 : 1) * i;
}

double lennard_jones(double r) {
  return 12 * (E / SIGMA) * (pow(SIGMA / r, 13) - pow(SIGMA / r, 7));
}

Vector calc_inertia_center(std::vector<Molecule> molecules) {
  Vector center = null();
  double mass = 0;
  for (int i = 0; i < static_cast<int>(molecules.size()); i++) {
    center += (molecules[i].coordinates.cur * molecules[i].mass);
    mass += molecules[i].mass;
  }
  return center / mass;
}

std::pair<double, Vector> calc_periodic_dist(Molecule tarMol, Molecule copMol) {
  Vector target = tarMol.coordinates.cur;
  Vector to_copy = copMol.coordinates.cur;
  Vector dummy = to_copy;
  for (int n = -1; n <= 1; n++) {
    for (int m = -1; m <= 1; m++) {
      for (int k = -1; k <= 1; k++) {
        dummy.x += m * SIDE_OF_SYSTEM;
        dummy.y += n * SIDE_OF_SYSTEM;
        dummy.z += k * SIDE_OF_SYSTEM;

        double d = distance(dummy, target);

        if (d < FORCE_RADIUS) {
          return std::pair<double, Vector>(
              d,
              Vector(target.x - dummy.x, target.y - dummy.y, target.z - dummy.z)
                  .normalize());
        }

        dummy = to_copy;
      }
    }
  }
  return std::pair<double, Vector>(0, Vector(0, 0, 0));
}

void calc_iner_force(std::vector<Molecule> *molecules, Delta iner) {
  for (int i = 0; i < molecules->size(); i++) {
    Delta dist = Delta(iner.cur - (*molecules)[i].coordinates.cur,
                       iner.prev - (*molecules)[i].coordinates.prev);

    Vector dM = (dist.cur | (*molecules)[i].force.cur) -
                (dist.prev | (*molecules)[i].force.prev);

    Delta coor = (*molecules)[i].coordinates;

    (*molecules)[i].iner_force.cur = Vector(
        (dist.cur.x - dist.prev.x) == 0 ? 0 : dM.x / (dist.cur.x - dist.prev.x),
        (dist.cur.y - dist.prev.y) == 0 ? 0 : dM.y / (dist.cur.y - dist.prev.y),
        (dist.cur.z - dist.prev.z) == 0 ? 0 : dM.z / (dist.cur.z - dist.prev.z));
  }
}
