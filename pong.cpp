#include "pong.hpp"

void RenderAndUpdate(sf::RenderWindow* window, const real32& dt){
  
    // Updating states

  player.dy = 0.f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      player.dy = -1.f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      player.dy = 1.f;

    // Ball leaves level
    if(b.sprite.getPosition().x < 0.f || b.sprite.getPosition().x > WINDOW_WIDTH
       || b.sprite.getPosition().y < 0 || b.sprite.getPosition().y > WINDOW_HEIGHT){
      b.sprite.setPosition(WINDOW_WIDTH / 2 - b.sprite.getGlobalBounds().width / 2,
		     WINDOW_HEIGHT / 2 - b.sprite.getGlobalBounds().width /2);
      b.dx = -maxBallSpeed;
      b.dy = 0.f;
      b.x_dir = -1.f;
      b.y_dir = 0.f;
    }
    // TODO(l4v): ball collision
    // Ball collision with paddles

    // Player right collision
    if(b.sprite.getPosition().x <=
       player.sprite.getPosition().x + player.sprite.getGlobalBounds().width
       && (b.sprite.getPosition().y + b.sprite.getGlobalBounds().height
	   >= player.sprite.getPosition().y
	   && b.sprite.getPosition().y <= player.sprite.getPosition().y
	   + player.sprite.getGlobalBounds().height))
       b.x_dir = 1.f;

    // Player up collision
    if(b.sprite.getPosition().y + b.sprite.getGlobalBounds().height >=
       player.sprite.getPosition().y
       && (b.sprite.getPosition().x >= player.sprite.getPosition().x
	   + player.sprite.getGlobalBounds().width
	   && b.sprite.getPosition().x + b.sprite.getGlobalBounds().width >=
	   player.sprite.getPosition().x))
       b.y_dir = -0.f;
    
    // TODO(l4v): Rest of Player and AI collisions
    // TODO(l4v): Ball "spin" depending on whether the paddle was moving
    // up or down
    // Calculate ball velocity
    b.dx += ballAccel * b.x_dir;
    b.dy += ballAccel * b.y_dir;

    // Ball speed limit
    if(b.dx > 0 && b.dx >= maxBallSpeed)
      b.dx = maxBallSpeed;
    if(b.dx < 0 && b.dx <= -maxBallSpeed)
      b.dx = -maxBallSpeed;
    if(b.dy > 0 && b.dy >= maxBallSpeed)
      b.dy = maxBallSpeed;
    if(b.dy < 0 && b.dy <= -maxBallSpeed)
      b.dy = -maxBallSpeed;
    
    
    // Update locations
    player.sprite.move(0.f, player.dy * paddleSpeed * dt);
    b.sprite.move(b.dx * dt, b.dy * dt);
    
    // Event handling
    sf::Event event;
    while (data.window->pollEvent(event))
      {
	if (event.type == sf::Event::Closed)
	data.window->close();
      }

    // Render stuff
    window->clear();
    
    window->draw(player.sprite);
    window->draw(ai.sprite);
    window->draw(b.sprite);
    
    window->display();
}

int main(int argc, char* argv[]){
    //game_data data;
    sf::Texture paddleTexture;
    sf::Clock clock;
    real32 dt = 0.f; // Time elapsed between frames
    
    paddleTexture.loadFromFile("paddle.png");
    player.sprite.setTexture(paddleTexture);
    ai.sprite.setTexture(paddleTexture);
    b.sprite.setTexture(paddleTexture);

    b.sprite.setTextureRect(sf::IntRect(
				    sf::Vector2i(0, 0),
				    sf::Vector2i(10, 10)));
    player.sprite.setPosition(100, WINDOW_HEIGHT / 2 - player.sprite.getGlobalBounds().height / 2);
    ai.sprite.setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2 - player.sprite.getGlobalBounds().height / 2);
    b.sprite.setPosition(WINDOW_WIDTH / 2 - b.sprite.getGlobalBounds().width / 2,
		     WINDOW_HEIGHT / 2 - b.sprite.getGlobalBounds().width /2);
 

    data.window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "PONG!");
    data.window->setFramerateLimit(60);

    b.dx = -maxBallSpeed;
    b.dy = 0.f;
    b.x_dir = -1.f;
    b.y_dir = 0.f;
    
    // Main game loop
    while (data.window->isOpen())
        {
	  
         RenderAndUpdate(data.window, dt);

	 // Get elapsed time
	 dt = clock.getElapsedTime().asSeconds();

	 // Reset the clock
	 clock.restart();
        }
    
    free(data.window);

    return 0;
}
