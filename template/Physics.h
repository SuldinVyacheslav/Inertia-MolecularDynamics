#include "Molecule.h"
#include <vector>
using namespace std;

extern double maxwell(double V);
extern double get_maxwell_dist();
extern Vector get_maxwell_vector();
extern double lennard_jones(double d);
extern Vector calc_inertia_center(vector<Molecule> Molecules);
extern pair<double,Vector> calc_periodic_dist(Molecule tarMol, Molecule copMol);
extern Vector calc_iner_force(vector<Molecule> &Molecules, Delta iner);
extern double calculateN(double Temp); // 0,002669 sqrt(M*T) / диамтр^2
// рид шервуд свойства газов и жидкостей cnh 455

// графики движения крупной с инерцией и без
// годограф силы
// 