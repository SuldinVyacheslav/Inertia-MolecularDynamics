#include <math.h>
#include "Constants.h"

const int ACC = 500;

const int MOL_SIDE = 4;
const int NUMBER_OF_MOLECULES = MOL_SIDE * MOL_SIDE * MOL_SIDE;
const double DELTA_T = pow(10, -15);
const int X = 1000;
const int Y = X;

const double FORCE_RADIUS = 2 * SIGMA;

const double SIDE_OF_SYSTEM = FORCE_RADIUS * MOL_SIDE;

const double ARGON_RADIUS = 1.92 * pow(10, -10);

const double SIGMA = (3.54 * pow(10, -10)); // = 3.54 А
const double E = (1.283343 * pow(10, -21)); // = 0.00801 eB

const double ARGON_MASS = (6.6335209 * pow(10, -26));

const double SCALE = SIDE_OF_SYSTEM / X; // = 1 px 10 в -6

const double DIST = FORCE_RADIUS;
