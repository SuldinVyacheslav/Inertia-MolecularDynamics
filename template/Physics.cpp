#include <vector>
#include <math.h>

#include "Physics.h"

double maxwell(double V)
{
    double m = 6.63 * pow(10, -26);
    int T = 300;
    double k = 1.38 * pow(10, -23);
    double A1 = (1 / sqrt(M_PI)) * sqrt(m / (2 * k * T));
    return A1 * exp(-((m * pow(V, 2)) / (2 * k * T)));
}

Vector get_maxwell_vector()
{
    return Vector(get_maxwell_dist(),
                  get_maxwell_dist(),
                  get_maxwell_dist());
}

double get_maxwell_dist()
{
    double sum = 0;
    std::vector<double> vel;
    for (int i = 0; i < 66 * 18; i++)
    {
        double prob = maxwell(i);
        vel.push_back(prob);
        sum += prob;
    }
    double b = rand() % 100;

    int i = 0;
    double cur = 0;

    for (i = 0; i < vel.size() && b > cur * 100; i++)
    {
        cur += vel[i] / sum;
    }
    return (rand() % 2 == 0 ? -1 : 1) * i;
}

double lennard_jones(double r)
{
    return 12 * (E / SIGMA) * (pow(SIGMA / r, 13) - pow(SIGMA / r, 7));
}

Vector calc_inertia_center(std::vector<Molecule> Molecules)
{
    Vector Center = Vector(0, 0, 0);
    double mass = 0;
    for (int i = 0; i < Molecules.size(); i++)
    {
        Center += (Molecules[i].coordinates * Molecules[i].mass);
        mass += Molecules[i].mass;
    }
    return Center * (1 / mass);
}

pair<double, Vector> calc_periodic_dist(Vector target, Vector to_copy)
{
    Vector dummy = to_copy;
    // target.print();
    // to_copy.print();
    for (int n = -1; n <= 1; n++)
    {
        for (int m = -1; m <= 1; m++)
        {
            for (int k = -1; k <= 1; k++)
            {
                dummy.x += m * SIDE_OF_SYSTEM;
                dummy.y += n * SIDE_OF_SYSTEM;
                dummy.z += k * SIDE_OF_SYSTEM;

                double d = distance(dummy, target);

                if (d < 2 * SIGMA)
                {
                    return pair<double, Vector>(d, Vector(target.x - dummy.x,
                                                          target.y - dummy.y,
                                                          target.z - dummy.z));
                }

                dummy = to_copy;
            }
        }
    }
    return pair<double, Vector>(0, Vector(0, 0, 0));
}

void deltaInretion(std::vector<Molecule> first, Vector c, Vector cn)
{
    for (int i = 0; i < first.size(); i++)
    {
        Vector M = first[i].force * distance(c, first[i].coordinates) - first[i].force_prev * distance(cn, first[i].coordinates_prev);

        first[i].force += Vector(M.x * (1 / (first[i].coordinates_prev.x - first[i].coordinates.x)),
                                M.y * (1 / (first[i].coordinates_prev.y - first[i].coordinates.y)),
                                M.z * (1 / (first[i].coordinates_prev.z - first[i].coordinates.z)));
    }
}