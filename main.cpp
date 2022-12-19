// Copyright 2022 Suldin Vyacheslav

#include "Graph.h"
#include "Physics.h"
#include "Visualization.h"

using std::pair;
using std::vector;

int main(int argc, char *argv[]) {
  vector<Molecule> molecules1{Molecule(Vector(1, 1, -1), null()),
                              Molecule(Vector(3, 3, 3), null()),
                              Molecule(Vector(-5, 4, 2), null())};

  Vector prev_center = null();
  Vector center = calc_inertia_center(molecules1);

  molecules1[0].force = Delta(null(), Vector(2, 2, 2));
  molecules1[1].force = Delta(null(), Vector(0, 1, 4));
  molecules1[2].force = Delta(null(), Vector(1, 4, -1));
  calc_iner_force(&molecules1, Delta(prev_center, center));
  molecules1[2].iner_force.cur.print("ASD ");
  return 0;
  App visualization;
  visualization.setup(argc, argv);

  Graph kinetic_e = Graph(sf::Color::Blue);
  Graph force = Graph(sf::Color::Blue);
  Graph force_iner = Graph(sf::Color::Red);
  Graph iner = Graph(sf::Color::Red);

  vector<Molecule> molecules;
  molecules.reserve(NUMBER_OF_MOLECULES);

  Delta inertion = Delta();

  setup_positions(&molecules);
  inertion.cur = calc_inertia_center(molecules);
  while (visualization.main.isOpen()) {
    visualization.is_close();

    for (int i = 0; i < molecules.size(); i++) {
      draw(&visualization.main,
           10 + ((1000 * ARGON_RADIUS / (2 * MOL_SIDE * SIGMA)) /
                 SIDE_OF_SYSTEM) *
                    molecules[i].coordinates.cur.z,
           sf::Color::Cyan, molecules[i].coordinates.cur.x,
           molecules[i].coordinates.cur.y, SCALE);
      draw(&visualization.main,
           ((1000 * ARGON_RADIUS / (2 * MOL_SIDE * SIGMA)) / SIDE_OF_SYSTEM) *
               molecules[i].coordinates.cur.z,
           i == 76 ? sf::Color::Red : sf::Color::Green,
           molecules[i].coordinates.cur.x, molecules[i].coordinates.cur.y,
           SCALE / 1.01);
    }

    draw(&visualization.main, 4, sf::Color::Red,
         inertion.prev.x - (inertion.cur.x - inertion.prev.x) * 1000,
         inertion.prev.y - (inertion.cur.y - inertion.prev.y) * 1000, SCALE);

    draw(&visualization.main, 4, sf::Color::Yellow, inertion.cur.x,
         inertion.cur.y, SCALE);
    calc_force(&molecules);

    iner.update_graph(&visualization.force,
                      molecules[0].iner_force.cur.length());
    force.update_graph(&visualization.force, molecules[0].force.cur.length());

    inertion.prev = inertion.cur;
    for (int i = 0; i < molecules.size(); i++) {
      molecules[i].semi_step();
    }

    inertion.cur = calc_inertia_center(molecules);
    calc_iner_force(&molecules, inertion);

    double velocity = 0;
    for (int i = 0; i < molecules.size(); i++) {
      velocity += molecules[i].velocity.x * molecules[i].velocity.x +
                  molecules[i].velocity.y * molecules[i].velocity.y;
    }

    kinetic_e.update_graph(&visualization.kinetic, velocity);

    visualization.display();
  }
}
