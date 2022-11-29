#include "Graph.h"

#include <vector>

Graph::Graph(sf::Color color): color(color)
{
    values.reserve(1000);
}

std::vector<double> values;

void Graph::update_graph(sf::RenderWindow *window, double new_value)
{
    if (values.size() < 1000)
    {
        values.push_back(new_value);
        top = new_value > top ? new_value : top;
    }
    else
    {
        top = 0;
        for (int i = 0; i < values.size(); i++)
        {
            values[i] = values[i + 1];
            top = values[i] > top ? values[i] : top;
        }
        values[values.size()] = new_value;
    }
    for (int i = values.size(); i > 1; i--)
    {
        draw(window, 2, color,
             i,
             (values[i] / top*0.75) * 1000, 1);
    }
}

void draw(sf::RenderWindow *window, float radius, sf::Color color, double x, double y, double scale)
{
    sf::CircleShape center(radius);
    center.setFillColor(color);
    center.setPosition(x / scale, y / scale);
    window->draw(center);
}