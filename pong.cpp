#include "pong.hpp"

// bool32 CheckCollision(real32 x1, real32 y1, real32 w1, real32 h1,
// 		    real32 x2, real32 y2, real32 w2, real32 h2)
// {
//   if((x1 + w1 > x2) && (x1 <= x2 + w2) && (y1 + h1 >= y2) && (y1 <= y2 + h2))
//     {
//       return true;
//     }
//   return false;
// }

// void drawTriangle(){
//   glClearColor(0.4, 0.4, 0.4, 0.4);
//     glClear(GL_COLOR_BUFFER_BIT);

//     glColor3f(1.0, 1.0, 1.0);
//     glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

//         glBegin(GL_TRIANGLES);
//                 glVertex3f(-0.7, 0.7, 0);
//                 glVertex3f(0.7, 0.7, 0);
//                 glVertex3f(0, -1, 0);
//         glEnd();

//     glFlush();
// }

// void RenderAndUpdate(game_memory* Memory, sf::RenderWindow* window, const real32& dt){
//   // // TODO(l4v): Use the game state
  
//   game_state* State = (game_state*)Memory->TransientStorage;
//   if(!Memory->isInitialized){
    
//     State->paddleTexture.loadFromFile("paddle.png");
//     // std::cout << &State->paddleTexture << " " << &(State->isInitialized) << " "
//     // 	      << &State->player << " " << &State->ai << std::endl;
    
//     State->player.sprite.setTexture(State->paddleTexture);
//     State->player.sprite.setTexture(State->paddleTexture);
//     State->ai.sprite.setTexture(State->paddleTexture);
//     State->b.sprite.setTexture(State->paddleTexture);

//     State->b.sprite.setTextureRect(sf::IntRect(
// 					sf::Vector2i(0, 0),
// 					sf::Vector2i(10, 10)));
//     State->player.sprite.setPosition(100, WINDOW_HEIGHT / 2 - State->player.sprite.getGlobalBounds().height / 2);
//     State->ai.sprite.setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2 - State->player.sprite.getGlobalBounds().height / 2);
//     State->b.sprite.setPosition(WINDOW_WIDTH / 2 - State->b.sprite.getGlobalBounds().width / 2,
// 			 WINDOW_HEIGHT / 2 - State->b.sprite.getGlobalBounds().width /2);
  
//     State->player.width = State->player.sprite.getGlobalBounds().width;
//     State->player.height = State->player.sprite.getGlobalBounds().height;
//     State->ai.width = State->ai.sprite.getGlobalBounds().width;
//     State->ai.height = State->ai.sprite.getGlobalBounds().height;

//     State->b.width = State->b.sprite.getGlobalBounds().width;
//     State->b.height = State->b.sprite.getGlobalBounds().height;
//     State->b.dx = -maxBallSpeed;
//     State->b.dy = 0.f;
//     Memory->isInitialized++;  
//   }
  
//   // Updating states
  
//   State->player.dy = 0.f;
//   if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//     State->player.dy = -1.f;

//   if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//     State->player.dy = 1.f;
  
//   // Ball hits top
//   if(State->b.sprite.getPosition().y <= 0.f){
//     State->b.sprite.setPosition(State->b.sprite.getPosition().x, 0.f);
//     State->b.dy *= -1.f;
//   }

//   // Ball hits bottom
//   if(State->b.sprite.getPosition().y + State->b.height >= WINDOW_HEIGHT){
//     State->b.sprite.setPosition(State->b.sprite.getPosition().x, WINDOW_HEIGHT - State->b.height);
//     State->b.dy *= -1.f;
//   }
  
//   // Ball leaves level
//   if(State->b.sprite.getPosition().x < 0.f || State->b.sprite.getPosition().x > WINDOW_WIDTH){
//     State->b.sprite.setPosition(WINDOW_WIDTH / 2 - State->b.width / 2,
// 			 WINDOW_HEIGHT / 2 - State->b.height /2);
//     State->b.dx = -maxBallSpeed;
//     State->b.dy = 0.f;
//   }

//   // Player Collision
//   if(CheckCollision(State->player.sprite.getPosition().x,
// 		    State->player.sprite.getPosition().y,
// 		    State->player.width, State->player.height,
// 		    State->b.sprite.getPosition().x,
// 		    State->b.sprite.getPosition().y,
// 		    State->b.width, State->b.height))
//     {
//       State->b.dx *= -1.f;
//       State->b.sprite.setPosition(State->player.sprite.getPosition().x + State->player.width, State->b.sprite.getPosition().y);
//       // Collision with upper third
//       if(State->b.sprite.getPosition().y + State->b.height / 2 <=
// 	 State->player.sprite.getPosition().y
// 	 + State->player.height / 3)
// 	{
// 	  State->b.dy = -State->b.dx;
// 	}
//       // Collision with lower third
//       else if(State->b.sprite.getPosition().y + State->b.height / 2 >=
// 	      State->player.sprite.getPosition().y +
// 	      (2.f/3.f) * State->player.height)
// 	{
// 	  State->b.dy = State->b.dx;
// 	}
//       // Collision with middle
//       else{
// 	State->b.dy = 0.f;
//       }
//   }

//   // AI collision
//    if(CheckCollision(State->b.sprite.getPosition().x,
// 		    State->b.sprite.getPosition().y,
// 		    State->b.width, State->b.height,
// 		    State->ai.sprite.getPosition().x,
// 		    State->ai.sprite.getPosition().y,
// 		    State->ai.width, State->ai.height))
//     {
//     State->b.sprite.setPosition(State->ai.sprite.getPosition().x
// 			 - State->b.width,
// 			 State->b.sprite.getPosition().y);
//     State->b.dx *= -1.f;
    
//     // Collision with upper third
//     if(State->b.sprite.getPosition().y + State->b.height / 2 <=
//        State->ai.sprite.getPosition().y
//        + State->ai.height / 3)
//       {
// 	State->b.dy = State->b.dx;
//       }
//     // Collision with lower third
//     else if(State->b.sprite.getPosition().y + State->b.height / 2 >=
// 	    State->ai.sprite.getPosition().y +
// 	    (2.f/3.f) * State->ai.height)
//       {
// 	State->b.dy = -State->b.dx;
//       }
//     // Collision with middle
//     else{
//       State->b.dy = 0.f;
//     }
//   }
  
//   // Ball speed limit
//   if(State->b.dx > 0 && State->b.dx >= maxBallSpeed)
//     State->b.dx = maxBallSpeed;
//   if(State->b.dx < 0 && State->b.dx <= -maxBallSpeed)
//     State->b.dx = -maxBallSpeed;
//   if(State->b.dy > 0 && State->b.dy >= maxBallSpeed)
//     State->b.dy = maxBallSpeed;
//   if(State->b.dy < 0 && State->b.dy <= -maxBallSpeed)
//     State->b.dy = -maxBallSpeed;
    
    
//   // Update locations

//   // Player location update
//   State->player.sprite.move(0.f, State->player.dy * paddleSpeed * dt);
//   if(State->player.sprite.getPosition().y <= 0.f)
//     State->player.sprite.setPosition(State->player.sprite.getPosition().x, 0.f);
//   if(State->player.sprite.getPosition().y + State->player.height >= WINDOW_HEIGHT)
//     State->player.sprite.setPosition(State->player.sprite.getPosition().x,
// 			      WINDOW_HEIGHT - State->player.height);
  
//   // Ball location update
//   State->b.sprite.move(State->b.dx * dt, State->b.dy * dt);
    
//   // Event handling
//   sf::Event event;
//   while (window->pollEvent(event))
//     {
//       if (event.type == sf::Event::Closed)
// 	window->close();
//     }

  
//   // Render stuff
//   window->clear();
    
//   window->draw(State->player.sprite);
//   window->draw(State->ai.sprite);
//   window->draw(State->b.sprite);
    
//   window->display();
// }


// NOTE(l4v): These should be loaded from a seperate file
// NOTE(l4v): "#version 300 es\n" should be "#version 330 core\n"
const char *vertexShaderSource = //"#version 300 es\n"
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource =
  //  "#version 300 es\n"
  "#version 330 core\n"
  "out highp vec4 FragColor;\n"
  "uniform highp vec4 triangleColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = triangleColor;\n//vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n\0";

const char *fragmentShaderSource1 =
  //  "#version 300 es\n"
    "#version 330 core\n"
  "out highp vec4 FragColor;\n"
  "void main()\n"
  "{\n"
  "   FragColor = vec4(0.0f, 0.5f, 0.5f, 1.0f);\n"
  "}\n\0";


int main(int argc, char* argv[]){
#if PONG_INTERNAL
  void *BaseAddress = (void *)Gibibytes(250);
#else
  void *BaseAddress = (void *)(0);
#endif

  SDL_Window* window;
  SDL_GLContext glContext;
  SDL_Event sdlEvent;

  bool quit;
  
  // NOTE(l4v): Allocating new memory and subdividing it into parts
  // game_memory GameMemory{};
  // GameMemory.PermanentStorageSize = Mebibytes(60);
  // GameMemory.TransientStorageSize = Mebibytes(100);
  
  // uint64 TotalStorageSize = GameMemory.PermanentStorageSize
  //   + GameMemory.TransientStorageSize;
  // GameMemory.PermanentStorage = mmap(BaseAddress, TotalStorageSize,
  // 				     PROT_READ | PROT_WRITE,
  // 				     MAP_ANONYMOUS | MAP_PRIVATE,
  // 				     -1,
  // 				     0);
  // GameMemory.TransientStorage = (uint8 *)(GameMemory.PermanentStorage)
  //   + GameMemory.PermanentStorageSize;
  
  // // NOTE(l4v): Check if memory allocation failed 
  // Assert(GameMemory.PermanentStorage);  
  // Assert(GameMemory.TransientStorage);
  // Memory->isInitialized++;
  /*
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG!");
  window.setFramerateLimit(60);
  
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
  */
  quit = false;
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  if(SDL_Init(SDL_INIT_VIDEO) > 0)
    {
      std::cout << "SDL could not be initialized" << std::endl;
      return 1;
    }

  // NOTE(l4v): Create the window
  window = SDL_CreateWindow("Pong!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL
			    | SDL_WINDOW_SHOWN);

  if(!window)
    {
      std::cout << "Window was not created" << std::endl;
      return 1;
    }

  glContext = SDL_GL_CreateContext(window);

  if(!glContext)
    {
      std::cout << "GL context could not be created" << std::endl;
      return 1;
    }
  // NOTE(l4v): Initialize GLEW
  glewInit();
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  // NOTE(l4v): Array of vertices for the triangle (changed to draw 2 triangles for rectangle)
  real32 vertices[] = {
		       0.5f, 0.5f, 0.f,
		       0.5f, -0.5f, 0.f,
		       -0.5f, -0.5f, 0.f,
		       -0.5f, 0.5f, 0.f
  };

  // NOTE(l4v): For the 2 triangle exercise
  real32 triangle1[] = {
			// First
			-0.5f, 0.f, 0.f, // BL1
			-0.25f, 0.5f, 0.f, // M1
			0.f, 0.f, 0.f, // BR1 / 2
  };

  real32 triangle2[] = {
			// Second
			0.f, 0.f, 0.f,
			0.25f, 0.5f, 0.f, // M2
			0.5f, 0.f, 0.f // BR2
  };

  // NOTE(l4v): Indices for the EBO to draw a rectangle from 2 triangles
  uint32 indices[] = {
		      0, 1, 3,
		      1, 2, 3
  };


  // NOTE(l4v): Creating the element buffer object, EBO
  uint32 EBO;
  glGenBuffers(1, &EBO);
  
  // NOTE(l4v): Creating a VBO (vertex buffer object)
  uint32 VBO;
  glGenBuffers(1, &VBO);

  uint32 VBOs[2];
  glGenBuffers(2, VBOs);
  
  // NOTE(l4v): Creating a vertex shader object
  uint32 vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // NOTE(l4v): Attaching shader source code to the shader object
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // NOTE(l4v): Check if shader compilation failed
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX:COMPILATION_FAILED" << std::endl << infoLog << std::endl;
    }

  uint32 fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // NOTE(l4v): 2 shaders for exercise
  uint32 fragmentShaders[2];
  fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaders[0], 1, &fragmentShaderSource1, 0);
  glCompileShader(fragmentShaders[0]);

  fragmentShaders[1] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaders[1], 1, &fragmentShaderSource, 0);
  glCompileShader(fragmentShaders[1]);
  
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success)
    {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
    }

  // NOTE(l4v): Creating a shader program object
  uint32 shaderProgram;
  shaderProgram = glCreateProgram();

  uint32 shaderProgram1;
  shaderProgram1 = glCreateProgram();

  glAttachShader(shaderProgram1, vertexShader);
  glAttachShader(shaderProgram1, fragmentShaders[0]);
  glLinkProgram(shaderProgram1);
  
  // NOTE(l4v): Attaching and linking shaders to the program
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // NOTE(l4v): Check for program linking failure
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success)
    {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED" << std::endl << infoLog << std::endl;
    }

  // NOTE(l4v): Deleting objects since they're not required after linking them
  // to the shader program
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // NOTE(l4v): Generating a VAO
  uint32 VAO;
  glGenVertexArrays(1, &VAO);

  uint32 VAOs[2];
  glGenVertexArrays(2, VAOs);
  
  // NOTE(l4v): Init code, done only once, unless object changes frequently
  // 1. bind VAO
  glBindVertexArray(VAO);
  // 2. copy vertices array in a buffer for OpenGL to use

  // NOTE(l4v): Bind current VBO to GL_ARRAY_BUFFER
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  
  // NOTE(l4v): Binding the EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  // NOTE(l4v): Copy the triangle vertex data to the buffer
  // GL_STATIC_DRAW - when the data very rarely changes
  // GL_DYNAMIC_DRAW - when the data changes very often
  // GL_STREAM_DRAW - when the data changes every time it's drawn
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // NOTE(l4v): Copying the indices to the buffer (changed for exercise)
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  // 3. set vertex attribute pointers
  // NOTE(l4v): Telling OpenGL how to interpret the vertex data in memory
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // NOTE(l4v): Binding and copying data for the first triangle
  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // NOTE(l4v): Binding and copying data for the second triangle
  glBindVertexArray(VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  real32 time = 0.f;
  
  while(!quit)
    {
      while(SDL_PollEvent(&sdlEvent))
	{
	  if(sdlEvent.type == SDL_QUIT)
	    quit = true;

	  if(sdlEvent.type == SDL_KEYDOWN)
	    if(sdlEvent.key.keysym.sym == SDLK_ESCAPE)
	      quit = true;
	}

      // NOTE(l4v): Set background to black c// olor
      glClearColor(0.2f, 0.3f, 0.3f, 1.f);
      // NOTE(l4v): Clear the color buffer
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // NOTE(l4v): Draw the triangle

      // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      
      // NOTE(l4v): Activate the shader program
      glUseProgram(shaderProgram);
      // glBindVertexArray(VAO);
      // glDrawArrays(GL_TRIANGLES, 0, 6); // Was used for drawing a single triangle from vertices
      // NOTE(l4v): Drawing from the element buffer using indices
      // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      glUseProgram(shaderProgram1);
      
      // NOTE(l4v): Drawing first triangle
      glBindVertexArray(VAOs[0]);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      // NOTE(l4v): Changing triangle color
      glUseProgram(shaderProgram);
      time += 0.01f;
      real32 timeValue = SDL_GetTicks();
      real32 greenValue = (sin(time))
	/ 2.0f + 0.5f;

      int32 vertexColorLocation = glGetUniformLocation(shaderProgram,
						       "triangleColor");
  
      glUniform4f(vertexColorLocation, 0.f, greenValue, 0.f, 1.f);
      // NOTE(l4v): Drawing second triangle
      glBindVertexArray(VAOs[1]);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      
      // NOTE(l4v): Unbinding the array
      glBindVertexArray(0);
      
      // draw_triangle();
      // Note(l4v): Swap the buffers
      SDL_GL_SwapWindow(window);      
    }

  // CONTINUE ON https://learnopengl.com/Getting-started/Hello-Triangle

  // Destroy window
  SDL_DestroyWindow(window);
  window = 0;
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  SDL_Quit();
  
  return 0;

}
