#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// For debugging, if the expression is false, an attempt
// is made to write to the 0 pointer, which automatically causes
// a crash. 
#define Assert(Expression) if(!(Expression)) {*(int*)0 = 0;}
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define internal static
#define global_variable static
#define local_persist static

#define Kibibytes(Value) ((Value)*1024)
#define Mebibytes(Value) (Kilobytes(Value)*1024)
#define Gigibytes(Value) (Megabytes(Value)*1024)

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

void RenderAndUpdate(sf::RenderWindow*);

