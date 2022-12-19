// Copyright 2022 Suldin Vyacheslav

#include "Graph.h"

#include <vector>

Graph::Graph(sf::Color color) : color(color) { values.reserve(X); }

std::vector<double> values;

void Graph::update_graph(sf::RenderWindow *window, double new_value) {
  int size = static_cast<int>(values.size());
  top = 0;
  if (size < X) {
    values.push_back(new_value);
    top += new_value;
  } else {
    for (int i = 0; i < size; i++) {
      values[i] = values[i + 1];
      top += values[i];
    }
    values[size] = new_value;
    top += new_value;
  }
  top /= X;
  for (int i = size; i > 1; i--) {
    draw(window, 2, color, i, Y - (values[i] / top * 0.75) * Y, 1);
  }
}

void draw(sf::RenderWindow *window, float radius, sf::Color color, double x,
          double y, double scale) {
  sf::CircleShape center(radius);
  center.setFillColor(color);
  center.setPosition(x / scale, y / scale);
  window->draw(center);
}
