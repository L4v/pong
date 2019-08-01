#include "pong.hpp"

void RenderAndUpdate(game_memory* Memory, sf::RenderWindow* window, const real32& dt){
  // TODO(l4v): Use the game state
  if(!Memory->isInitialized){
  }
  
  // Updating states
  
  player.dy = 0.f;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    player.dy = -1.f;

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    player.dy = 1.f;
  
  // Ball hits top
  if(b.sprite.getPosition().y <= 0.f){
    b.sprite.setPosition(b.sprite.getPosition().x, 0.f);
    b.dy *= -1.f;
  }

  // Ball hits bottom
  if(b.sprite.getPosition().y + b.height >= WINDOW_HEIGHT){
    b.sprite.setPosition(b.sprite.getPosition().x, WINDOW_HEIGHT - b.height);
    b.dy *= -1.f;
  }
  
  // Ball leaves level
  if(b.sprite.getPosition().x < 0.f || b.sprite.getPosition().x > WINDOW_WIDTH){
    b.sprite.setPosition(WINDOW_WIDTH / 2 - b.width / 2,
			 WINDOW_HEIGHT / 2 - b.height /2);
    b.dx = -maxBallSpeed;
    b.dy = 0.f;
  }
  // TODO(l4v): ball collision
  // Ball collision with paddles

  // Player right collision
  if((b.sprite.getPosition().x <= player.sprite.getPosition().x + player.width && b.sprite.getPosition().x + b.width >= player.sprite.getPosition().x)
     && (b.sprite.getPosition().y + b.height >= player.sprite.getPosition().y && b.sprite.getPosition().y <= player.sprite.getPosition().y + player.height)){
    b.dx *= -1.f;
    b.sprite.setPosition(player.sprite.getPosition().x + player.width, b.sprite.getPosition().y);
    // Collision with upper third
    if(b.sprite.getPosition().y + b.height / 2 <=
       player.sprite.getPosition().y
       + player.height / 3)
      {
	b.dy = -b.dx;
      }
    // Collision with lower third
    else if(b.sprite.getPosition().y + b.height / 2 >=
	    player.sprite.getPosition().y +
	    (2.f/3.f) * player.height)
      {
	b.dy = b.dx;
      }
    // Collision with middle
    else{
      b.dy = 0.f;
    }
  }

  // AI left collision
  if((b.sprite.getPosition().x + b.width >=
      ai.sprite.getPosition().x
      && b.sprite.getPosition().x <=
      ai.sprite.getPosition().x + ai.width)
     && (b.sprite.getPosition().y + b.height
	 >= ai.sprite.getPosition().y
	 && b.sprite.getPosition().y <= ai.sprite.getPosition().y
	 + ai.height)){
    b.sprite.setPosition(ai.sprite.getPosition().x
			 - b.width,
			 b.sprite.getPosition().y);
    b.dx *= -1.f;
    
    // Collision with upper third
    if(b.sprite.getPosition().y + b.height / 2 <=
       ai.sprite.getPosition().y
       + ai.height / 3)
      {
	b.dy = b.dx;
      }
    // Collision with lower third
    else if(b.sprite.getPosition().y + b.height / 2 >=
	    ai.sprite.getPosition().y +
	    (2.f/3.f) * ai.height)
      {
	b.dy = -b.dx;
      }
    // Collision with middle
    else{
      b.dy = 0.f;
    }
  }
  
  // Calculate ball velocity
  b.sprite.move(b.dx * dt, b.dy * dt);
  
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
  if(player.sprite.getPosition().y <= 0.f)
    player.sprite.setPosition(player.sprite.getPosition().x, 0.f);
  if(player.sprite.getPosition().y + player.height >= WINDOW_HEIGHT)
    player.sprite.setPosition(player.sprite.getPosition().x,
			      WINDOW_HEIGHT - player.height);
  // b.sprite.move(b.dx * dt, b.dy * dt);
    
  // Event handling
  sf::Event event;
  while (window->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	window->close();
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
#if PONG_INTERNAL
  void *BaseAddress = (void *)Gibibytes(500);
#else
  void *BaseAddress = (void *)(0);
#endif

  // NOTE(l4v): Allocating new memory and subdividing it into parts
  game_memory GameMemory{};
  GameMemory.PermanentStorageSize = Mebibytes(60);
  GameMemory.TransientStorageSize = Gibibytes(4);

  uint64 TotalStorageSize = GameMemory.PermanentStorageSize
    + GameMemory.TransientStorageSize;
  GameMemory.PermanentStorage = mmap(BaseAddress, TotalStorageSize,
				     PROT_READ | PROT_WRITE,
				     MAP_ANONYMOUS | MAP_PRIVATE,
				     -1,
				     0);
  GameMemory.TransientStorage = (uint8 *)(GameMemory.PermanentStorage)
    + GameMemory.PermanentStorageSize;

  // NOTE(l4v): Check if memory allocation failed
  Assert(GameMemory.PermanentStorage);


  // GameState->window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG!");
  //GameState->window.setFrameRateLimit(60);
  //Memory->isInitialized++;

  // TODO(l4v): FIX THIS AAA!
  window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG!");
  
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
  
  player.width = player.sprite.getGlobalBounds().width;
  player.height = player.sprite.getGlobalBounds().height;
  ai.width = ai.sprite.getGlobalBounds().width;
  ai.height = ai.sprite.getGlobalBounds().height;

  b.width = b.sprite.getGlobalBounds().width;
  b.height = b.sprite.getGlobalBounds().height;
  b.dx = -maxBallSpeed;
  b.dy = 0.f;
    
  // Main game loop
  while (window.isOpen())
    {
	  
      RenderAndUpdate(&GameMemory, &window, dt);

      // Get elapsed time
      dt = clock.getElapsedTime().asSeconds();

      // Reset the clock
      clock.restart();
    }
    
  //free(data.window);
  return 0;
}
