#include <SFML/Graphics.hpp>

#define LIST_OF_WINDOW \
    X(main)            \
    X(kinetic)         \
    X(force)

class App
{
public:
    App(int argc, char *argv[]);


#define X(name) sf::RenderWindow name;
    LIST_OF_WINDOW
#undef X

    void add_window(sf::RenderWindow *window, sf::String title);

    void is_close();

    void display();

    void add_if(const char *name, char *cmd, sf::RenderWindow *window);
};