#include <algorithm>
#include <iostream>
#include <math.h>
#include <string.h>

#include "Constants.h"
#include "Graph.h"
#include "Physics.h"
#include "Vector.h"
#include "Visualization.h"

using namespace std;

bool comp(Molecule v, Molecule u) {
  return v.coordinates.cur.z < u.coordinates.cur.z;
}
void setup_positions(vector<Molecule> &molecules) {
  for (int i = 1; i < MOL_SIDE + 1; i++) {
    for (int j = 1; j < MOL_SIDE + 1; j++) {
      for (int k = 1; k < MOL_SIDE + 1; k++) {
        Molecule to_add = Molecule(
            Vector((i + 0.5) * DIST, (j + 0.5) * DIST, (k + 0.5) * DIST),
            get_maxwell_vector());

        molecules.push_back(to_add);
      }
    }
  }
}

void calc_force(vector<Molecule> &molecules) {
  for (int i = 0; i < molecules.size(); i++) {
    Vector force_sum = Vector(0, 0, 0);

    for (int k = i + 1; k < molecules.size(); k++) {
      pair<double, Vector> dist_dir =
          calc_periodic_dist(molecules[i], molecules[k]);

      if (dist_dir.first != 0) {
        // if (d.molecules < 2 * ARGON_RADIUS)
        // {
        //     molecules[i].Collide(molecules[k]);
        // }
        Vector force = dist_dir.second * lennard_jones(dist_dir.first);
        force_sum += force;

        molecules[k].force.cur += -force;
      }
    }
    molecules[i].force.cur += force_sum;
  }
}

// vector<sf::RenderWindow *> setup(int argc, char *argv[])
// {
//     sf::RenderWindow window;
//     window.create(sf::VideoMode(X, Y), "simulation");

//     vector<sf::RenderWindow *> windows;
//     windows.reserve(10);

//     windows.push_back(&window);

//     char *graphs[2] = {"-kin", "-force"};
//     for (int i = 0; i < argc; i++)
//     {
//         for (int j = 0; j < 2; j++)
//         {
//             if (strcmp(argv[i], graphs[j]))
//             {
//                 if (strcmp(graphs[j], "-kin"))
//                 {
//                     sf::RenderWindow kinetic;
//                     kinetic.create(sf::VideoMode(X, Y), "kinetic");
//                     windows.push_back(&kinetic);
//                 }
//                 else if (strcmp(graphs[j], "-force"))
//                 {
//                     sf::RenderWindow inertia;
//                     inertia.create(sf::VideoMode(X, Y), "inertia force");
//                     windows.push_back(&inertia);
//                 }
//             }
//         }
//     }
// }

int main(int argc, char *argv[]) {
  App visualization;
  visualization.setup(argc, argv);

  // vector<sf::RenderWindow *> windows = setup(argc, argv);

  Graph kinetic_e = Graph(sf::Color::Blue);
  Graph force = Graph(sf::Color::Blue);
  Graph force_iner = Graph(sf::Color::Red);
  Graph iner = Graph(sf::Color::Green);

  vector<Molecule> molecules;
  molecules.reserve(NUMBER_OF_MOLECULES);

  // vector<Vector> fp;

  // for (int i = 0; i < 40 * NUMBER_OF_MOLECULES; i++)
  // {
  //     fp.push_back(Vector(0, 0, 0));
  // }
  Delta inertion = Delta(null(), null());

  setup_positions(molecules);

  while (visualization.main.isOpen()) {

    visualization.is_close();

    // sort(molecules.begin(), molecules.end(), comp);
    for (int i = 0; i < molecules.size(); i++) {
      // if (count % ACC == 0)
      // {
      //     if (current == ACC / 8 * NUMBER_OF_MOLECULES)
      //     {
      //         current = 0;
      //     }
      //     fp[current] = (Vector(molecules[i].coordinates.x,
      //     molecules[i].coordinates.y, molecules[i].coordinates.z));
      //     current++;
      // }
      draw(&visualization.main,
           10 + ((1000 * ARGON_RADIUS / (2 * MOL_SIDE * SIGMA)) /
                 SIDE_OF_SYSTEM) *
                    molecules[i].coordinates.cur.z,
           sf::Color::Cyan, molecules[i].coordinates.cur.x,
           molecules[i].coordinates.cur.y, SCALE);
      draw(&visualization.main,
           ((1000 * ARGON_RADIUS / (2 * MOL_SIDE * SIGMA)) / SIDE_OF_SYSTEM) *
               molecules[i].coordinates.cur.z,
           i == 0 ? sf::Color::Red : sf::Color::Green,
           molecules[i].coordinates.cur.x, molecules[i].coordinates.cur.y,
           SCALE / 1.01);
    }

    draw(&visualization.main, 4, sf::Color::Red,
         inertion.prev.x - (inertion.cur.x - inertion.prev.x) * 1000,
         inertion.prev.y - (inertion.cur.y - inertion.prev.y) * 1000, SCALE);

    draw(&visualization.main, 4, sf::Color::Yellow, inertion.cur.x,
         inertion.cur.y, SCALE);

    // for (int i = 0; i < fp.size(); i++)
    // {
    //     BaseSet(&window, 2, sf::Color::Green,
    //             fp[i].x + 20 * SCALE,
    //             fp[i].y + 20 * SCALE);
    // }

    calc_force(molecules);

    // int d = 0;
    // Vector forc;
    // Vector M = molecules[0].force.cur * distance(inertion.cur,
    // molecules[0].coordinates.cur) -
    //            molecules[0].force.prev * distance(inertion.prev,
    //            molecules[0].coordinates.prev);

    // cout << "M: ";
    // M.print();
    // Delta cool = molecules[0].coordinates;
    // cout << "prev coord: ";
    // cool.prev.print();
    // cout << "cur coord: ";
    // cool.cur.print();

    // cout << "delta x" << (cool.prev.x - cool.cur.x) << endl;

    // forc = Vector(M.x / (cool.prev.x - cool.cur.x),
    //               M.y / (cool.prev.y - cool.cur.y),
    //               M.z / (cool.prev.z - cool.cur.z));
    // cout << "new force: ";
    // forc.print();
    // cout << "force before: ";
    // molecules[0].force.cur.print();
    // molecules[0].force.cur += forc;
    // cout << "force after : ";
    // molecules[0].force.cur.print();
    // cout << "velocity: ";
    // molecules[0].velocity.print();
    // cout << "______________\n";
    // scanf("%d", &d);

    Vector prev = calc_iner_force(molecules, inertion);

    //(molecules[0].force.cur - prev).print();

    double velocity = 0;
    for (int i = 0; i < molecules.size(); i++) {
      velocity += molecules[i].velocity.x * molecules[i].velocity.x +
                  molecules[i].velocity.y * molecules[i].velocity.y;
    }
    Vector abc = molecules[0].force.cur; // - iner_force;

    iner.update_graph(&visualization.force, prev.length());
    kinetic_e.update_graph(&visualization.kinetic, velocity);
    // force_iner.update_graph(&visualization.force, (molecules[0].force.cur +
    // iner_force).length());
    force.update_graph(&visualization.force, molecules[0].force.cur.length());
    // graph(molecules, &kinetic, kin, velocity);
    // graph(molecules, &inertia, ine, ine1, molecules[0].force.length(),
    // abc.length());
    inertion.prev = inertion.cur;

    inertion.cur = calc_inertia_center(molecules);
    for (int i = 0; i < molecules.size(); i++) {
      molecules[i].semiStep();
    }
    visualization.display();
  }
}