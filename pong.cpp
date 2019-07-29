#include "pong.hpp"


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
