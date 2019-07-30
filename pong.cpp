#include "pong.hpp"

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;

void render(sf::RenderWindow* window){
    window->clear();

    window->draw(player);
    window->draw(ai);

    window->display();
}

int main(int argc, char* argv[]){
    game_data data;
    sf::Texture paddleTexture;

    paddleTexture.loadFromFile("paddle.png");
    player = sf::Sprite(paddleTexture);
    ai = sf::Sprite(paddleTexture);

    player.setPosition(100, WINDOW_HEIGHT / 2 - player.getGlobalBounds().height / 2);
    ai.setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2 - player.getGlobalBounds().height / 2);

    data.window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "PONG!");
    data.window->setFramerateLimit(60);


    while (data.window->isOpen())
        {

            render(data.window);

            sf::Event event;
            while (data.window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    data.window->close();
            }
        }

    free(data.window);

    return 0;
}
