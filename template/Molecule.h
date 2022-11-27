#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "Vector.h"
#include "Constants.h"

class Molecule
{
public:
    Molecule(Vector coor, Vector vel);
    void Base();
    void SemiStep();
    void Verlet();

    void Periodic();
    void Collide(Molecule &with);
    
    Vector coordinates;

    Vector velocity;

    Vector force;

    Vector force_prev;

    Vector coordinates_prev;

    double mass = MASS;

    double radius = 1;
};