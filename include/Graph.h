#include "Constants.h"
#include "Vector.h"
#include "math.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

class Graph {
public:
  Graph(sf::Color color);

  void update_graph(sf::RenderWindow *window, double new_value);

  std::vector<double> values;

  double top;

  sf::Color color;
};

void draw(sf::RenderWindow *window, float radius, sf::Color color, double x,
          double y, double scale);
