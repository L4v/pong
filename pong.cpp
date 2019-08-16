#include "pong.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

const char* load_shader(const char* path)
{
  char* shaderText = 0;
  int64 length;

  FILE* file = fopen(path, "rb");
  
  if(file)
    {
      fseek(file, 0, SEEK_END);
      length = ftell(file);
      fseek(file, 0, SEEK_SET);
      shaderText = (char*)malloc(length); // TODO(l4v): Use memory arenas
      if(shaderText)
	{
	  fread(shaderText, 1, length, file);
	}
      fclose(file);
    }
  return shaderText;
}

// NOTE(l4v): These should be loaded from a seperate file
// NOTE(l4v): "#version 300 es\n" should be "#version 330 core\n"

const char* fragmentShaderSource = load_shader("fragment_shader.glsl");
const char* vertexShaderSource = load_shader("vertex_shader.glsl");

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

  // NOTE(l4v): Array of vertices for rectangle
  real32 vertices[] = {
		       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		       0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  // NOTE(l4v): Positions of 10 cubes
  
  glm::vec3 cubePositions[] = {
			       glm::vec3( 0.0f,  0.0f,  0.0f), 
			       glm::vec3( 2.0f,  5.0f, -15.0f), 
			       glm::vec3(-1.5f, -2.2f, -2.5f),  
			       glm::vec3(-3.8f, -2.0f, -12.3f),  
			       glm::vec3( 2.4f, -0.4f, -3.5f),  
			       glm::vec3(-1.7f,  3.0f, -7.5f),  
			       glm::vec3( 1.3f, -2.0f, -2.5f),  
			       glm::vec3( 1.5f,  2.0f, -2.5f), 
			       glm::vec3( 1.5f,  0.2f, -1.5f), 
			       glm::vec3(-1.3f,  1.0f, -1.5f)  
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
  
  // NOTE(l4v): Creating a vertex shader object
  uint32 vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  //  const char* vertexShaderSource = load_shader("vertex_shader.glsl");
  
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
  
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success)
    {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
    }

  // NOTE(l4v): Creating a shader program object
  uint32 shaderProgram;
  shaderProgram = glCreateProgram();
  
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

  // Positions
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Texture coords
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
			(void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // NOTE(l4v): TEXTURE 1
  
  // NOTE(l4v): Binding the texture
  uint32 texture1, texture2;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  // NOTE(l4v): Tell stb to flip image on y-axis
  stbi_set_flip_vertically_on_load(true);
  
  // NOTE(l4v): Set wrapping and filtering options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  // NOTE(l4v): Loading and generating the actual texture
  // Texture variables
  int32 width, height, nChannels;
  // TODO(l4v): Make use of memory arenas
  uint8 *data;

  // NOTE(l4v): Loading first image
  data = stbi_load("container.jpg", &width, &height, &nChannels, 0);
  if(data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
  else
    {
      std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD" << std::endl;
    }
  // NOTE(l4v): Frees the image data
  stbi_image_free(data);

  // NOTE(l4v): TEXTURE 2
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);

  // NOTE(l4v): Set wrapping and filtering options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  // NOTE(l4v): Loading second image
  data = stbi_load("awesomeface.png", &width, &height, &nChannels, 0);
  if(data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
  stbi_image_free(data);

  glUseProgram(shaderProgram);
  glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
  glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

  // TODO(l4v): Should group these things
  // -----------------------------------
  
  // NOTE(l4v): Enables the z-buffer
  glEnable(GL_DEPTH_TEST);

  // NOTE(l4v): Camera variables

  camera_struct camera;
  camera.model = glm::mat4(1.f);
  camera.projection;
  camera.view = glm::mat4(1.f);
  
  camera.pos   = glm::vec3(0.0f, 0.0f,  3.0f);
  camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
  camera.up    = glm::vec3(0.0f, 1.0f,  0.0f);
  camera.speed = 0.5f;

  // NOTE(l4v): Gets the locations of uniforms
  int32 mLocs[3] = {
		       glGetUniformLocation(shaderProgram, "model"),
		       glGetUniformLocation(shaderProgram, "view"),
		       glGetUniformLocation(shaderProgram, "projection")
  };

  
  // NOTE(l4v): For getting delta time
  real64 dt = 0.0;
  int64 now = SDL_GetPerformanceCounter();
  int64 last = 0;

  // NOTE(l4v): Disable cursor
  SDL_ShowCursor(SDL_DISABLE);

  // NOTE(l4v): Capture the mouse
  // SDL_SetWindowGrab(window, SDL_TRUE);
  SDL_CaptureMouse(SDL_TRUE);
  SDL_SetRelativeMouseMode(SDL_TRUE);
  real32 mouseSensitivity = 0.5f;
  real32 pitch = 0.f;
  real32 yaw = -90.f;
  camera.fov = 45.f;

  while(!quit)
    {
      // NOTE(l4v): Gets the delta time
      now = SDL_GetPerformanceCounter();
      dt = ((real64)((now - last))) / SDL_GetPerformanceFrequency();
      last = now;

      // NOTE(l4v): Set camera speed
      camera.speed = 2.5f * dt;
      
      while(SDL_PollEvent(&sdlEvent))
	{

	  // NOTE(l4v): WINDOW
	  if(sdlEvent.type == SDL_QUIT)
	    quit = true;

	  // NOTE(l4v): KEYBOARD
	  if(sdlEvent.type == SDL_KEYDOWN)
	    {
	      if(sdlEvent.key.keysym.sym == SDLK_ESCAPE)
		quit = true;
	      if(sdlEvent.key.keysym.sym == SDLK_w)
		camera.pos += camera.speed * camera.front;
	      if(sdlEvent.key.keysym.sym == SDLK_s)
		camera.pos -= camera.speed * camera.front;
	      if(sdlEvent.key.keysym.sym == SDLK_a)
		camera.pos -= glm::normalize(glm::cross(camera.front,
						       camera.up))
		  * camera.speed;
	      if(sdlEvent.key.keysym.sym == SDLK_d)
		camera.pos += glm::normalize(glm::cross(camera.front,
						       camera.up))
		  * camera.speed;
	       
	    }

	  // NOTE(l4v): MOUSE MOVEMENT
	  if(sdlEvent.type == SDL_MOUSEMOTION)
	    {
	      
	      yaw += sdlEvent.motion.xrel * mouseSensitivity;
	      pitch += -sdlEvent.motion.yrel * mouseSensitivity;

	      if(pitch > 89.0f) pitch = 89.0f;
	      if(pitch < -89.0f) pitch = -89.0f;

	    }

	  // NOTE(l4v): MOUSE WHEEL
	  if(sdlEvent.type == SDL_MOUSEWHEEL)
	    {
	      if(sdlEvent.wheel.y > 0 && camera.fov >= 1.f && camera.fov < 45.f)
		camera.fov += sdlEvent.wheel.y;
	      if(sdlEvent.wheel.y < 0 && camera.fov > 1.f && camera.fov <= 45.f)
		camera.fov += sdlEvent.wheel.y;
	    }
	  
	}
      
      glm::vec3 front;
      front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
      front.y = sin(glm::radians(pitch));
      front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
      camera.front = glm::normalize(front);

      // NOTE(l4v): Projection matrix, gives a feeling of perspective
      camera.projection = glm::perspective(glm::radians(camera.fov),
				    (real32) WINDOW_WIDTH / (real32) WINDOW_HEIGHT, 0.1f, 100.0f);
      
      // NOTE(l4v): Sets the world view
      camera.view = glm::lookAt(
			 camera.pos,
			 camera.pos + camera.front,
			 camera.up
			 );
      
      // NOTE(l4v): Set background to black color
      glClearColor(0.2f, 0.3f, 0.3f, 1.f);
      
      // NOTE(l4v): Clear the color buffer
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      // NOTE(l4v): Activate the shader program
      glUseProgram(shaderProgram);

      glUniformMatrix4fv(mLocs[0], 1, GL_FALSE, glm::value_ptr(camera.model));
      glUniformMatrix4fv(mLocs[1], 1, GL_FALSE, glm::value_ptr(camera.view));
      glUniformMatrix4fv(mLocs[2], 1, GL_FALSE, glm::value_ptr(camera.projection));
      
      // NOTE(l4v): Setting active texture unit and bind texture
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture1);

      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, texture2);
      
      // NOTE(l4v): Bind the VAO
      glBindVertexArray(VAO);

      // NOTE(l4v): Draw 10 cubes AND ROTATE THEM
      for(uint32 i = 0; i < 10; i ++)
	{
	  glm::mat4 model = glm::mat4(1.f);
	  model = glm::translate(model, cubePositions[i]);
	  float angle = 20.f * i;
	  model = glm::rotate(model, glm::radians(angle ),
			      glm::vec3(1.f, 0.3f, 0.5f));
	  glUniformMatrix4fv(mLocs[0], 1, GL_FALSE, glm::value_ptr(model));

	  glDrawArrays(GL_TRIANGLES, 0, 36);
	}
      
      // Note(l4v): Swap the buffers
      SDL_GL_SwapWindow(window);      
    }

  // Destroy window
  SDL_DestroyWindow(window);
  window = 0;
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  SDL_Quit();
  
  return 0;

}
