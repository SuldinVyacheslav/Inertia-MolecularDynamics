// Copyright 2022 Suldin Vyacheslav

#ifndef INCLUDE_GRAPH_H_
#define INCLUDE_GRAPH_H_

#include "Constants.h"
#include <SFML/Graphics.hpp>

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

#endif
