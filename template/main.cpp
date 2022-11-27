#include <SFML/Graphics.hpp>

#include <iostream>
#include <string.h>
#include <math.h>
#include <chrono>
#include <execution> // parallel

#include "Vector.h"    // Класс работы с векторами
#include "Constants.h" // Константы для СИ
#include "Physics.h"   // Начальное распределение скоростей

using namespace std;

void draw(sf::RenderWindow *window, float radius, sf::Color color, double x, double y, double scale)
{
    sf::CircleShape center(radius);
    center.setFillColor(color);
    center.setPosition(x / scale, y / scale);
    window->draw(center);
}

void graph(vector<Molecule> molecules, sf::RenderWindow *window, vector<int> &kin, double value)
{

    double x = 1.3 * pow(10, 8);

    if (kin.size() < 1000)
    {
        kin.push_back(value);
    }
    else
    {
        for (int i = 0; i < kin.size(); i++)
        {
            kin[i] = kin[i + 1];
        }
        kin[kin.size()] = value;
    }
    for (int i = kin.size(); i > 1; i--)
    {
        draw(window, 1, sf::Color::Yellow,
             i,
             (kin[i] / x) * 1000 * 10, 1);
    }
    window->display();
}

int main(int argc, char *argv[])
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(X, Y), "simulation");
    sf::RenderWindow kinetic;
    kinetic.create(sf::VideoMode(X, Y), "kinetic");
    sf::RenderWindow inertia;
    inertia.create(sf::VideoMode(X, Y), "inertia force");
    vector<int> kin;
    kin.reserve(1000);

    vector<int> ine;
    ine.reserve(1000);

    vector<Molecule> molecules;
    molecules.reserve(NUMBER_OF_MOLECULES);

    // vector<Vector> fp;

    // for (int i = 0; i < 40 * NUMBER_OF_MOLECULES; i++)
    // {
    //     fp.push_back(Vector(0, 0, 0));
    // }
    Vector inertion_center_prev = Vector(0, 0, 0);
    Vector inertion_center = Vector(0, 0, 0);

    for (int i = 1; i < MOL_SIDE + 1; i++)
    {
        for (int j = 1; j < MOL_SIDE + 1; j++)
        {
            for (int k = 1; k < MOL_SIDE + 1; k++)
            {
                Molecule to_add = Molecule(Vector((i + 0.5) * DIST, (j + 0.5) * DIST, (k + 0.5) * DIST), get_maxwell_vector());
                to_add.velocity.print();
                molecules.push_back(to_add);
            }
        }
    }

    int count = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        kinetic.clear();
        window.clear();
        inertia.clear();

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

            draw(&window,
                 10 + ((1000 * ARGON_RADIUS / (2 * MOL_SIDE * SIGMA)) / SIDE_OF_SYSTEM) * molecules[i].coordinates.z,
                 sf::Color::Cyan,
                 molecules[i].coordinates.x,
                 molecules[i].coordinates.y, SCALE);
            draw(&window,
                 ((1000 * ARGON_RADIUS / (2 * MOL_SIDE * SIGMA)) / SIDE_OF_SYSTEM) * molecules[i].coordinates.z,
                 sf::Color::Green,
                 molecules[i].coordinates.x,
                 molecules[i].coordinates.y, SCALE);
        }

        inertion_center_prev = inertion_center;
        inertion_center.x = inertion_center.y = inertion_center.z = 0;

        inertion_center = calc_inertia_center(molecules);

        draw(&window, 4, sf::Color::Red,
             inertion_center_prev.x - (inertion_center.x - inertion_center_prev.x) * 1000,
             inertion_center_prev.y - (inertion_center.y - inertion_center_prev.y) * 1000, SCALE);

        draw(&window, 4, sf::Color::Yellow,
             inertion_center.x,
             inertion_center.y, SCALE);

        // for (int i = 0; i < fp.size(); i++)
        // {
        //     BaseSet(&window, 2, sf::Color::Green,
        //             fp[i].x + 20 * SCALE,
        //             fp[i].y + 20 * SCALE);
        // }

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
        deltaInretion(molecules, inertion_center_prev, inertion_center);
        for (int i = 0; i < molecules.size(); i++)
        {
            molecules[i].SemiStep();
        }

        if (count % 1000 == 0)
        {
            double velocity = 0;
            for (int i = 0; i < molecules.size(); i++)
            {
                velocity += molecules[i].velocity.x * molecules[i].velocity.x + molecules[i].velocity.y * molecules[i].velocity.y;
            }

            graph(molecules, &kinetic, kin, velocity);
            graph(molecules, &inertia, ine, molecules[0].force.length());
        }

        for (int i = 0; i < molecules.size(); i++)
        {
            molecules[i].force = Vector(0, 0, 0);
        }
        window.display();
    }
}
