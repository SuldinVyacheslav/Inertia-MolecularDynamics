#include <iostream>
#include <string.h>

#include "Visualization.h"
#include "Constants.h"

void App::add_window(sf::RenderWindow *window, sf::String title)
{
    window->create(sf::VideoMode(X, Y), title);
}

void App::add_if(const char *name, char *cmd, sf::RenderWindow *window)
{
    if (!strcmp(name, cmd))
    {
        add_window(window, (sf::String)name);
    }
}


App::App(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
#define X(name) add_if(#name, argv[i], &name);
        LIST_OF_GRAPHS
#undef X
    }
}

void App::is_close()
{
    sf::Event event;
#define X(name)                                  \
    {                                            \
        sf::Event event;                         \
        while (name.pollEvent(event))            \
        {                                        \
            if (event.type == sf::Event::Closed) \
                name.close();                    \
        }                                        \
        name.clear();                            \
    }
    LIST_OF_GRAPHS
#undef X
}

void App::display()
{
#define X(name) name.display();
    LIST_OF_GRAPHS
#undef X
}