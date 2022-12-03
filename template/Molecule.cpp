#include "Molecule.h"

#include <vector>

Delta::Delta(Vector prev, Vector cur) : prev(prev), cur(cur)
{
}

Molecule::Molecule(Vector coor, Vector vel) : coordinates(Delta(null(), coor)),
                                              velocity(vel),
                                              force(Delta(null(), null()))
{
}

void Molecule::semiStep()
{
    coordinates.prev = coordinates.cur;

    Vector acc = force.prev / mass;

    coordinates.cur += (velocity * DELTA_T) + acc * (pow(DELTA_T, 2) / 2);

    Vector semi_vel = velocity + acc * (DELTA_T / 2);

    acc = force.cur / mass;

    velocity = semi_vel + acc * (DELTA_T / 2);

    force.prev = force.cur;

    force.cur = null();

    periodic();
}

void Molecule::verlet()
{
    coordinates.prev = coordinates.cur;

    Vector acc = force.prev / mass;

    coordinates.cur += (velocity * DELTA_T) + acc * (pow(DELTA_T, 2) / 2);

    Vector accN = force.cur / mass;

    velocity += (acc + accN) * (DELTA_T / 2);

    periodic();
}

void Molecule::base()
{
    coordinates.prev = coordinates.cur;

    coordinates.cur += velocity * DELTA_T; // X' = X + V * dT

    velocity += (force.cur / mass) * DELTA_T; // V' = V + a * dT   where a = F/m

    periodic(); // V'
}

void Check(double &cor)
{
    if (cor >= SIDE_OF_SYSTEM || cor <= 0)
    {
        cor += (cor <= 0 ? 1 : -1) * SIDE_OF_SYSTEM;
    }
}
void Molecule::periodic()
{
    Check(coordinates.cur.x);
    Check(coordinates.cur.y);
    Check(coordinates.cur.z);
}

Vector getNorm(Vector v, Vector u)
{
    return Vector(v.y * u.z - v.z * u.y,
                  -(v.x * u.z - v.x * v.z),
                  v.x * u.y - u.x * v.x)
        .normalize();
}
Vector getProj(Vector b, Vector a)
{
    return b * (a.x + a.y + a.z);
}

Vector toOld(Vector v, std::vector<Vector> A)
{
    return Vector(A[0].x + A[1].x + A[2].x,
                  A[0].y + A[1].y + A[2].y,
                  A[0].z + A[1].z + A[2].z);
}
void Molecule::collide(Molecule &with)
{
    // Vector oX = (with.coordinates - this->coordinates).normalize();
    // Vector oZ = getNorm(this->velocity, with.velocity);
    // Vector oY = getNorm(oX, oZ);
    // Vector Vx = getProj(oX, this->velocity);
    // Vector Ux = getProj(oX, with.velocity);
    // Vector newVx = (Vx * (this->mass - with.mass) + Ux * 2 * with.mass) / (this->mass + with.mass);
    // Vector newUx = (Vx * 2 * this->mass + Ux * (with.mass - this->mass)) / (this->mass + with.mass);

    // std::vector<Vector> A = {Vector(oX.x, oX.y, oX.z), Vector(oY.x, oY.y, oY.z), Vector(oZ.x, oZ.y, oZ.z)};
    // this->velocity = toOld(Vector(newVx.x, getProj(oY, this->velocity).y, 0), A);
    // with.velocity = toOld(Vector(newUx.x, getProj(oZ, this->velocity).y, 0), A);
}