#include <iostream>
#include <string.h>
#include <math.h>

#include "Vector.h"    // Класс работы с векторами
#include "Constants.h" // Константы для СИ
#include "Physics.h"   // Начальное распределение скоростей
#include "Graph.h"
#include "Visualization.h"

using namespace std;

void setup_positions(vector<Molecule> &molecules)
{
    for (int i = 1; i < MOL_SIDE + 1; i++)
    {
        for (int j = 1; j < MOL_SIDE + 1; j++)
        {
            for (int k = 1; k < MOL_SIDE + 1; k++)
            {
                Molecule to_add = Molecule(Vector((i + 0.5) * DIST, (j + 0.5) * DIST, (k + 0.5) * DIST), get_maxwell_vector());

                molecules.push_back(to_add);
            }
        }
    }
}

void calc_force(vector<Molecule> &molecules)
{
    for (int i = 0; i < molecules.size(); i++)
    {
        Vector force_sum = Vector(0, 0, 0);

        for (int k = i + 1; k < molecules.size(); k++)
        {
            pair<double, Vector> dist_dir = calc_periodic_dist(molecules[i].coordinates, molecules[k].coordinates);

            if (dist_dir.first != 0)
            {
                // if (d.molecules < 2 * ARGON_RADIUS)
                // {
                //     molecules[i].Collide(molecules[k]);
                // }
                Vector force = dist_dir.second.normalize() * lennard_jones(dist_dir.first);

                force_sum += force;

                molecules[k].force += -force;
            }
        }
        molecules[i].force += force_sum;
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

int main(int argc, char *argv[])
{
    App visualization = App(argc, argv);

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
    Vector inertion_center_prev = Vector(0, 0, 0);
    Vector inertion_center = Vector(0, 0, 0);

    setup_positions(molecules);

    int count = 0;
    while (visualization.main.isOpen())
    {

        visualization.is_close();

        for (int i = 0; i < molecules.size(); i++)
        {
            // if (count % ACC == 0)
            // {
            //     if (current == ACC / 8 * NUMBER_OF_MOLECULES)
            //     {
            //         current = 0;
            //     }
            //     fp[current] = (Vector(molecules[i].coordinates.x, molecules[i].coordinates.y, molecules[i].coordinates.z));
            //     current++;
            // }

            draw(&visualization.main,
                 10 + ((1000 * ARGON_RADIUS / (2 * MOL_SIDE * SIGMA)) / SIDE_OF_SYSTEM) * molecules[i].coordinates.z,
                 sf::Color::Cyan,
                 molecules[i].coordinates.x,
                 molecules[i].coordinates.y, SCALE);
            draw(&visualization.main,
                 ((1000 * ARGON_RADIUS / (2 * MOL_SIDE * SIGMA)) / SIDE_OF_SYSTEM) * molecules[i].coordinates.z,
                 i == 0 ? sf::Color::Red : sf::Color::Green,
                 molecules[i].coordinates.x,
                 molecules[i].coordinates.y, SCALE);
        }

        inertion_center_prev = inertion_center;

        inertion_center = calc_inertia_center(molecules);

        draw(&visualization.main, 4, sf::Color::Red,
             inertion_center_prev.x - (inertion_center.x - inertion_center_prev.x) * 1000,
             inertion_center_prev.y - (inertion_center.y - inertion_center_prev.y) * 1000, SCALE);

        draw(&visualization.main, 4, sf::Color::Yellow,
             inertion_center.x,
             inertion_center.y, SCALE);

        // for (int i = 0; i < fp.size(); i++)
        // {
        //     BaseSet(&window, 2, sf::Color::Green,
        //             fp[i].x + 20 * SCALE,
        //             fp[i].y + 20 * SCALE);
        // }

        calc_force(molecules);

        Vector iner_force = calc_iner_force(molecules, inertion_center_prev, inertion_center);

        if (count % 1000 == 0)
        {
            double velocity = 0;
            for (int i = 0; i < molecules.size(); i++)
            {
                velocity += molecules[i].velocity.x * molecules[i].velocity.x + molecules[i].velocity.y * molecules[i].velocity.y;
            }
            Vector abc = molecules[0].force; // - iner_force;

            iner.update_graph(&visualization.force,iner_force.length());
            kinetic_e.update_graph(&visualization.kinetic, velocity);
            force_iner.update_graph(&visualization.force, (molecules[0].force + iner_force).length());
            force.update_graph(&visualization.force, molecules[0].force.length());
            // graph(molecules, &kinetic, kin, velocity);
            // graph(molecules, &inertia, ine, ine1, molecules[0].force.length(), abc.length());
        }

        for (int i = 0; i < molecules.size(); i++)
        {
            molecules[i].SemiStep();
        }

        visualization.display();
    }
}
