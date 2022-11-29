#include <iostream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include "math.h"
#include "Vector.h"
#include "Constants.h"

class Graph
{
public:
    Graph(sf::Color color);

    void update_graph(sf::RenderWindow *window, double new_value);

    std::vector<double> values;

    double top = 0;

    sf::Color color;
};

void draw(sf::RenderWindow *window, float radius, sf::Color color, double x, double y, double scale);

