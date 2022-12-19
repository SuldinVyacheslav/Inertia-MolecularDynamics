// Copyright 2022 Suldin Vyacheslav

#include <SFML/Graphics.hpp>
#ifndef INCLUDE_VISUALIZATION_H_
#define INCLUDE_VISUALIZATION_H_

#define LIST_OF_WINDOW \
  X(main)              \
  X(kinetic)           \
  X(force)

class App {
 public:
  App();

  void setup(int argc, char *argv[]);

#define X(name) sf::RenderWindow name;
  LIST_OF_WINDOW
#undef X

  void add_window(sf::RenderWindow *window, sf::String title);

  void is_close();

  void display();

  void add_if(const char *name, char *cmd, sf::RenderWindow *window);
};

#endif  // INCLUDE_VISUALIZATION_H_
