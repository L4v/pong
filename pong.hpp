#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct game_data{
    sf::RenderWindow* window;
};

sf::Sprite player, ai;

// struct paddle{
//     int x;
//     int y;
//     int width;
//     int height;
// };

void render(sf::RenderWindow*);
