// Copyright 2022 Suldin Vyacheslav

#include "Visualization.h"

#include <string.h>

#include <iostream>

#include "Constants.h"

void App::setup(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
#define X(window) add_if(#window, argv[i], &window);
    LIST_OF_WINDOW
#undef X
  }
}

void App::add_window(sf::RenderWindow *window, sf::String title) {
  window->create(sf::VideoMode(X, Y), title);
}

void App::add_if(const char *name, char *cmd, sf::RenderWindow *window) {
  if (!strcmp(name, cmd)) {
    add_window(window, (sf::String)name);
  }
}

App::App() {}

void App::is_close() {
  sf::Event event;
#define X(name)                                          \
  {                                                      \
    sf::Event event;                                     \
    while (name.pollEvent(event)) {                      \
      if (event.type == sf::Event::Closed) name.close(); \
    }                                                    \
    name.clear(sf::Color::White);                        \
  }
  LIST_OF_WINDOW
#undef X
}

void App::display() {
#define X(name) name.display();
  LIST_OF_WINDOW
#undef X
}
