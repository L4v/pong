#include "pong.hpp"

bool32 CheckCollision(real32 x1, real32 y1, real32 w1, real32 h1,
		    real32 x2, real32 y2, real32 w2, real32 h2)
{
  if((x1 + w1 > x2) && (x1 <= x2 + w2) && (y1 + h1 >= y2) && (y1 <= y2 + h2))
    {
      return true;
    }
  return false;
}

void RenderAndUpdate(game_memory* Memory, sf::RenderWindow* window, const real32& dt){
  // // TODO(l4v): Use the game state
  
  game_state* State = (game_state*)Memory->TransientStorage;
  if(!Memory->isInitialized){

    State->player.sprite.setTexture(State->paddleTexture);
    State->ai.sprite.setTexture(State->paddleTexture);
    State->b.sprite.setTexture(State->paddleTexture);

    State->b.sprite.setTextureRect(sf::IntRect(
					sf::Vector2i(0, 0),
					sf::Vector2i(10, 10)));
    State->player.sprite.setPosition(100, WINDOW_HEIGHT / 2 - State->player.sprite.getGlobalBounds().height / 2);
    State->ai.sprite.setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2 - State->player.sprite.getGlobalBounds().height / 2);
    State->b.sprite.setPosition(WINDOW_WIDTH / 2 - State->b.sprite.getGlobalBounds().width / 2,
			 WINDOW_HEIGHT / 2 - State->b.sprite.getGlobalBounds().width /2);
  
    State->player.width = State->player.sprite.getGlobalBounds().width;
    State->player.height = State->player.sprite.getGlobalBounds().height;
    State->ai.width = State->ai.sprite.getGlobalBounds().width;
    State->ai.height = State->ai.sprite.getGlobalBounds().height;

    State->b.width = State->b.sprite.getGlobalBounds().width;
    State->b.height = State->b.sprite.getGlobalBounds().height;
    State->b.dx = -maxBallSpeed;
    State->b.dy = 0.f;
    Memory->isInitialized++;  
  }
  
  // Updating states
  
  State->player.dy = 0.f;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    State->player.dy = -1.f;

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    State->player.dy = 1.f;
  
  // Ball hits top
  if(State->b.sprite.getPosition().y <= 0.f){
    State->b.sprite.setPosition(State->b.sprite.getPosition().x, 0.f);
    State->b.dy *= -1.f;
  }

  // Ball hits bottom
  if(State->b.sprite.getPosition().y + State->b.height >= WINDOW_HEIGHT){
    State->b.sprite.setPosition(State->b.sprite.getPosition().x, WINDOW_HEIGHT - State->b.height);
    State->b.dy *= -1.f;
  }
  
  // Ball leaves level
  if(State->b.sprite.getPosition().x < 0.f || State->b.sprite.getPosition().x > WINDOW_WIDTH){
    State->b.sprite.setPosition(WINDOW_WIDTH / 2 - State->b.width / 2,
			 WINDOW_HEIGHT / 2 - State->b.height /2);
    State->b.dx = -maxBallSpeed;
    State->b.dy = 0.f;
  }

  // Player Collision
  if(CheckCollision(State->player.sprite.getPosition().x,
		    State->player.sprite.getPosition().y,
		    State->player.width, State->player.height,
		    State->b.sprite.getPosition().x,
		    State->b.sprite.getPosition().y,
		    State->b.width, State->b.height))
    {
      State->b.dx *= -1.f;
      State->b.sprite.setPosition(State->player.sprite.getPosition().x + State->player.width, State->b.sprite.getPosition().y);
      // Collision with upper third
      if(State->b.sprite.getPosition().y + State->b.height / 2 <=
	 State->player.sprite.getPosition().y
	 + State->player.height / 3)
	{
	  State->b.dy = -State->b.dx;
	}
      // Collision with lower third
      else if(State->b.sprite.getPosition().y + State->b.height / 2 >=
	      State->player.sprite.getPosition().y +
	      (2.f/3.f) * State->player.height)
	{
	  State->b.dy = State->b.dx;
	}
      // Collision with middle
      else{
	State->b.dy = 0.f;
      }
  }

  // AI collision
   if(CheckCollision(State->b.sprite.getPosition().x,
		    State->b.sprite.getPosition().y,
		    State->b.width, State->b.height,
		    State->ai.sprite.getPosition().x,
		    State->ai.sprite.getPosition().y,
		    State->ai.width, State->ai.height))
    {
    State->b.sprite.setPosition(State->ai.sprite.getPosition().x
			 - State->b.width,
			 State->b.sprite.getPosition().y);
    State->b.dx *= -1.f;
    
    // Collision with upper third
    if(State->b.sprite.getPosition().y + State->b.height / 2 <=
       State->ai.sprite.getPosition().y
       + State->ai.height / 3)
      {
	State->b.dy = State->b.dx;
      }
    // Collision with lower third
    else if(State->b.sprite.getPosition().y + State->b.height / 2 >=
	    State->ai.sprite.getPosition().y +
	    (2.f/3.f) * State->ai.height)
      {
	State->b.dy = -State->b.dx;
      }
    // Collision with middle
    else{
      State->b.dy = 0.f;
    }
  }
  
  // Ball speed limit
  if(State->b.dx > 0 && State->b.dx >= maxBallSpeed)
    State->b.dx = maxBallSpeed;
  if(State->b.dx < 0 && State->b.dx <= -maxBallSpeed)
    State->b.dx = -maxBallSpeed;
  if(State->b.dy > 0 && State->b.dy >= maxBallSpeed)
    State->b.dy = maxBallSpeed;
  if(State->b.dy < 0 && State->b.dy <= -maxBallSpeed)
    State->b.dy = -maxBallSpeed;
    
    
  // Update locations

  // Player location update
  State->player.sprite.move(0.f, State->player.dy * paddleSpeed * dt);
  if(State->player.sprite.getPosition().y <= 0.f)
    State->player.sprite.setPosition(State->player.sprite.getPosition().x, 0.f);
  if(State->player.sprite.getPosition().y + State->player.height >= WINDOW_HEIGHT)
    State->player.sprite.setPosition(State->player.sprite.getPosition().x,
			      WINDOW_HEIGHT - State->player.height);
  
  // Ball location update
  State->b.sprite.move(State->b.dx * dt, State->b.dy * dt);
    
  // Event handling
  sf::Event event;
  while (window->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	window->close();
    }

  
  // Render stuff
  window->clear();
    
  window->draw(State->player.sprite);
  window->draw(State->ai.sprite);
  window->draw(State->b.sprite);
    
  window->display();
}

int main(int argc, char* argv[]){
#if PONG_INTERNAL
  void *BaseAddress = (void *)Gibibytes(250);
#else
  void *BaseAddress = (void *)(0);
#endif

  // NOTE(l4v): Allocating new memory and subdividing it into parts
  game_memory GameMemory{};
    GameMemory.PermanentStorageSize = Mebibytes(60);
    GameMemory.TransientStorageSize = Mebibytes(100);

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
    Assert(GameMemory.TransientStorage);
  // GameState->window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG!");
  //GameState->window.setFrameRateLimit(60);
  // Memory->isInitialized++;

  window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG!");
  
  // sf::Texture paddleTexture;
  sf::Clock clock;
  real32 dt = 0.f; // Time elapsed between frames

  // Main game loop

  // real32 lastTime = 0.f;
  // real32 currentTime = 0.f;
  // real32 fps = 0.f;
  // sf::Clock fpsClock;
  while (window.isOpen())
    {
	  
      RenderAndUpdate(&GameMemory, &window, dt);

      // Get elapsed time
      dt = clock.getElapsedTime().asSeconds();

      // Reset the clock
      clock.restart();

      // currentTime = fpsClock.restart().asSeconds();
      // fps = 1.f / currentTime;
      // lastTime = currentTime;

      // std::cout << "S:" << fps << std::endl;
      // system("clear");
      
    }


  munmap(GameMemory.PermanentStorage, GameMemory.PermanentStorageSize);
  munmap(GameMemory.TransientStorage, GameMemory.TransientStorageSize);
  //free(data.window);
  return 0;
}
