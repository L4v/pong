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

internal const char* load_shader(const char* path)
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

internal glm::mat4 look_at(glm::vec3 cameraPos, glm::vec3 targetPos, glm::vec3 worldUp)
{
  // NOTE(l4v): Calculate the normalized direction vector of the camera
  // (the z axis)
  glm::vec3 direction = glm::normalize(cameraPos - targetPos);

  // NOTE(l4v): Calcualte the normalized right vector of the camera
  // (the x axis)
  glm::vec3 right = glm::normalize(glm::cross(worldUp, direction));

  // NOTE(l4v): Calculate the normalized up vector of the camera
  // (the y axis)
  glm::vec3 up = glm::normalize(glm::cross(direction, right));

  // NOTE(l4v): Translation matrix
  glm::mat4 translation(1.f);
  translation[3][0] = -cameraPos.x;
  translation[3][1] = -cameraPos.y;
  translation[3][2] = -cameraPos.z;

  // NOTE(l4v): Rotation matrix
  glm::mat4 rotation(1.f);
  // Right
  rotation[0][0] = right.x;
  rotation[1][0] = right.y;
  rotation[2][0] = right.z;
  // Up
  rotation[0][1] = up.x;
  rotation[1][1] = up.y;
  rotation[2][1] = up.z;
  // Direction
  rotation[0][2] = direction.x;
  rotation[1][2] = direction.y;
  rotation[2][2] = direction.z;

  return rotation * translation;
}

internal void check_shader_compilation(uint32 shader, shader_type type)
{
  // NOTE(l4v): Check if shader compilation failed
  int32 success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success)
    {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout <<
	(type == VERTEX ? "ERROR::SHADER::VERTEX:COMPILATION_FAILED"
	 : "ERROR::SHADER::FRAGMENT:COMPILATION_FAILED")
		<< std::endl << infoLog << std::endl;
    }  
}

internal void check_shader_program_link(uint32 program)
{
  int32 success;
  GLchar infoLog[512];
  // NOTE(l4v): Check for program linking failure
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success)
    {
      glGetProgramInfoLog(program, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED" << std::endl << infoLog << std::endl;
    }
}

internal uint32 load_texture(const char* path)
{
  uint32 id;
  glGenTextures(1, &id);
  
  int32 width, height, nComponents;

  uint8* data = stbi_load(path, &width, &height, &nComponents, 0);
  if(data)
    {
      GLenum format;
      if(nComponents == 1)
	format = GL_RED;
      else if(nComponents == 3)
	format = GL_RGB;
      else if(nComponents == 4)
	format = GL_RGBA;

      glBindTexture(GL_TEXTURE_2D, id);
      glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
		   GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		      GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    }
  else
    {
      std::cout << "ERROR::TEXTURE:FAILED_TO_LOAD(" << path << ")"
		<< std::endl;
    }
      stbi_image_free(data);
      return id;
}

internal inline void setVec3(uint32 shader, const char* variable, const glm::vec3& value)
{
  glUniform3fv(glGetUniformLocation(shader, variable), 1, &value[0]);
}

internal inline void setVec3(uint32 shader, const char* variable, real32 x, real32 y, real32 z)
{
  glUniform3f(glGetUniformLocation(shader, variable), x, y, z);
}

internal inline void setFloat(uint32 shader, const char* variable, real32 fValue)
{
  glUniform1f(glGetUniformLocation(shader, variable), fValue);
}

internal inline void setMat4(uint32 shader, const char* variable, const glm::mat4 &mat)
{
  glUniformMatrix4fv(glGetUniformLocation(shader, variable), 1, GL_FALSE, &mat[0][0]);
}

internal inline void setInt(uint32 shader, const char* variable, uint32 uValue)
{
  glUniform1i(glGetUniformLocation(shader, variable), uValue);
}

internal inline void setInt(uint32 shader, const char* variable, int32 iValue)
{
  glUniform1i(glGetUniformLocation(shader, variable), iValue);
}

internal inline bool check_aabb(real32 x1, real32 y1, real32 z1,
				real32 w1, real32 h1, real32 d1,
				real32 x2, real32 y2, real32 z2,
				real32 w2, real32 h2, real32 d2)
{
  if(std::abs(x1 - x2) < w1 + w2)
      if(std::abs(y1 - y2) < h1 + h2)
	  if(std::abs(z1 - z2) < d1 + d2)
	      return true;
  return false;
}

const char* cubeFragmentShaderSource = load_shader("cube.fs");
const char* cubeVertexShaderSource = load_shader("cube.vs");
const char* lightFragmentShaderSource = load_shader("light.fs");
const char* lightVertexShaderSource = load_shader("light.vs");
const char* paddleFragmentShaderSource = load_shader("paddle.fs");
const char* paddleVertexShaderSource = load_shader("paddle.vs");

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
  
  // NOTE(l4v): For getting delta time
  real64 dt = 0.0;
  int64 now = 0;
  int64 last = 0;
  
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
		       0.0f, 1.0f, 0.f, 0.0f, 1.0f,
		       1.0f, 0.0f, 0.f, 1.0f, 0.0f,
		       0.0f, 0.0f, 0.f, 0.0f, 0.0f, 
    
		       0.0f, 1.0f, 0.f, 0.0f, 1.0f,
		       1.0f, 1.0f, 0.f, 1.0f, 1.0f,
		       1.0f, 0.0f, 0.f, 1.0f, 0.0f
  };
  
  // NOTE(l4v): Positions of cubes
  
  glm::vec3 paddlePositions[] = {
				 glm::vec3( 0.0f, 0.0f, 0.f),
				 glm::vec3( 0.0f, 0.0f, 0.f)
  };

  // NOTE(l4v): Positions of point lights
  glm::vec3 ballPosition = glm::vec3(0.f, 0.f, 0.f);
  
  uint32 nPaddles = sizeof(paddlePositions) / sizeof(glm::vec3);
  uint32 nBalls = sizeof(ballPosition) / sizeof(glm::vec3);
  
  // NOTE(l4v): Vertex shaders
  // -------------------------
  uint32 lightVertexShader, paddleVertexShader;
  lightVertexShader = glCreateShader(GL_VERTEX_SHADER);
  paddleVertexShader = glCreateShader(GL_VERTEX_SHADER);
  
  // NOTE(l4v): Attaching shader source code to the shader object
  glShaderSource(lightVertexShader, 1, &lightVertexShaderSource, 0);
  glShaderSource(paddleVertexShader, 1, &paddleVertexShaderSource, 0);

  // NOTE(l4v): Shader compilation
  glCompileShader(lightVertexShader);
  check_shader_compilation(lightVertexShader, VERTEX);

  glCompileShader(paddleVertexShader);
  check_shader_compilation(paddleVertexShader, VERTEX);

  // NOTE(l4v): Fragment shaders
  // ---------------------------
  uint32 lightFragmentShader, paddleFragmentShader;
  lightFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  paddleFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // NOTE(l4v): Attaching shader source code to shader object
  glShaderSource(lightFragmentShader, 1, &lightFragmentShaderSource, 0);
  glShaderSource(paddleFragmentShader, 1, &paddleFragmentShaderSource, 0);
  
  // NOTE(l4v): Shader compilation
  glCompileShader(lightFragmentShader);
  check_shader_compilation(lightFragmentShader, FRAGMENT);

  glCompileShader(paddleFragmentShader);
  check_shader_compilation(paddleFragmentShader, FRAGMENT);

  // NOTE(l4v): Creating a shader program object
  uint32 lampShader, paddleShader;
  lampShader = glCreateProgram();
  glAttachShader(lampShader, lightVertexShader);
  glAttachShader(lampShader, lightFragmentShader);
  glLinkProgram(lampShader);
  check_shader_program_link(lampShader);

  paddleShader = glCreateProgram();
  glAttachShader(paddleShader, paddleVertexShader);
  glAttachShader(paddleShader, paddleFragmentShader);
  glLinkProgram(paddleShader);
  check_shader_program_link(paddleShader);
  
  // NOTE(l4v): Deleting objects since they're not required after linking them
  // to the shader program
  glDeleteShader(lightVertexShader);
  glDeleteShader(lightFragmentShader);
  glDeleteShader(paddleVertexShader);
  glDeleteShader(paddleFragmentShader);

  // NOTE(l4v): VAO, EBO, VBO...
  uint32
    lightVAO, lightVBO,
    paddleVBO, paddleVAO;

  // NOTE(l4v): PADDLE
  // -----------------

  // NOTE(l4v): Generating a VAO
  glGenVertexArrays(1, &paddleVAO);
  glBindVertexArray(paddleVAO);
  glGenBuffers(1, &paddleVBO);

  glBindBuffer(GL_ARRAY_BUFFER, paddleVBO);

  // NOTE(l4v): Position data
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
	       GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(real32),
			(void*) 0);
  glEnableVertexAttribArray(0);

  // NOTE(l4v): Texture data
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
	       GL_DYNAMIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(real32),
			(void*) (3 * sizeof(real32)));
  glEnableVertexAttribArray(1);

  // NOTE(l4v): LAMP
  // ---------------

  // NOTE(l4v): Generating a VAO
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  
  // NOTE(l4v): Position data
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);


  // NOTE(l4v): Paddle texture
  uint32 paddleTex;
  paddleTex = load_texture("paddle.png");
  glUseProgram(paddleShader);
  setInt(paddleShader, "tex", 0);

  // NOTE(l4v): Disable cursor
  SDL_ShowCursor(SDL_DISABLE);

  // NOTE(l4v): Capture the mouse
  SDL_CaptureMouse(SDL_TRUE);
  SDL_SetRelativeMouseMode(SDL_TRUE);

  // NOTE(l4v): Enables the z-buffer
  glEnable(GL_DEPTH_TEST);  
  
  // TODO(l4v): Should group these things
  // ------------------------------------

  // NOTE(l4v): Camera variables
  glm::mat4 model = glm::mat4(1.f);
  glm::mat4 projection;
  glm::mat4 view = glm::mat4(1.f);
			       
  // NOTE(l4v): Colors  
  glm::vec3 lightDir(-.2f, -1.f, -.3f);
  glm::vec3 lightPos = glm::vec3(1.f, 1.f, 1.f);

  // NOTE(l4v): Paddle and ball vars
  real32 paddleSpeed = 500.f;
  real32
    paddleWidth = 12.5f,
    paddleHeight = 50.f;
  real32 ballWidth = 100.f;
  real32 ballSpeed = 300.f;
  real32 dx = ballSpeed;
  real32 dy = 0.f;

  real32 paddleStartY1= (real32)WINDOW_HEIGHT * 0.5f - paddleHeight * 0.5f;
  real32 paddleStartX1 = 50.f;
  real32 paddleStartY2 = (real32)WINDOW_HEIGHT * 0.5f - paddleHeight * 0.5f;
  real32 paddleStartX2 = (real32)WINDOW_WIDTH - paddleWidth - 50.f;
  real32 ballStartX = (real32)WINDOW_WIDTH * .5f - ballWidth * .5f;
  real32 ballStartY = (real32)WINDOW_HEIGHT * .5f - ballWidth * .5f;
  

  paddlePositions[0].x = paddleStartX1;
  paddlePositions[0].y = paddleStartY1;
  paddlePositions[1].x = paddleStartX2;
  paddlePositions[1].y = paddleStartY2;

  ballPosition.x = ballStartX;
  ballPosition.y = ballStartY;
  
  now = SDL_GetPerformanceCounter();
  last = now;
  dt = 0.f;
  while(!quit)
    {
      // NOTE(l4v): Gets the delta time
      now = SDL_GetPerformanceCounter();
      dt = ((real64)((now - last))) / SDL_GetPerformanceFrequency();
      last = now;

      // TODO(l4v): MEMORY!!!
      const uint8* keystates;
      keystates = SDL_GetKeyboardState(0);

      // NOTE(l4v): Keyboard input irrelevant of events
      if(keystates[SDL_SCANCODE_W])
	paddlePositions[0].y -= paddleSpeed * dt;
	
      if(keystates[SDL_SCANCODE_S])
	paddlePositions[0].y += paddleSpeed * dt;

      if(keystates[SDL_SCANCODE_R])
	{
	  paddlePositions[0].y = paddleStartY1;
	  paddlePositions[1].y = paddleStartY2;

	  ballPosition.x = ballStartX;
	  ballPosition.y = ballStartY;
	  dx = ballSpeed;
	  dy = 0.f;
	}

      if(paddlePositions[0].y <= 0.f)
	paddlePositions[0].y = 0.f;
      if(paddlePositions[0].y + paddleHeight >= (real32)WINDOW_HEIGHT)
	paddlePositions[0].y = (real32)WINDOW_HEIGHT - paddleHeight;
      if(paddlePositions[1].y <= 0.f)
	paddlePositions[1].y = 0.f;
      if(paddlePositions[1].y + paddleHeight >= (real32)WINDOW_HEIGHT)
	paddlePositions[1].y = (real32)WINDOW_HEIGHT - paddleHeight;
      
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
	    }
	  // NOTE(l4v): MOUSE MOVEMENT
	  if(sdlEvent.type == SDL_MOUSEMOTION)
	    {

	    }
	}

      // NOTE(l4v): Projection matrix, gives a feeling of perspective
      projection = glm::ortho(-(real32)WINDOW_WIDTH * .5f,
			      (real32)WINDOW_WIDTH * .5f,
			      -(real32)WINDOW_HEIGHT * .5f,
			      (real32)WINDOW_HEIGHT * .5f,
			      -1.f, 1.f);

      // NOTE(l4v): Set background to black color
      glClearColor(0.1f, 0.1f, 0.1f, 1.f);
      
      // NOTE(l4v): Clear the color buffer
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glUseProgram(paddleShader);
      setMat4(paddleShader, "projection", projection);      

      // NOTE(l4v): Setting active texture unit and bind texture
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, paddleTex);

      // NOTE(l4v): Draw paddle
      for(size_t i = 0; i < nPaddles; ++i)
      	{
      	  glm::mat4 model = glm::mat4(1.f);
      	  model = glm::translate(model, paddlePositions[i]);
      	  model = glm::scale(model,
      			     glm::vec3(paddleWidth, paddleHeight, 1.f));
      	  setMat4(paddleShader, "model", model);

      	  glBindVertexArray(paddleVAO);
      	  glDrawArrays(GL_TRIANGLES, 0, 6);
      	}
      
      // NOTE(l4v): Lamp
      // ----------------
      glUseProgram(lampShader);
      glBindVertexArray(lightVAO);

      setMat4(lampShader, "projection", projection);

      real32 levelHeight = (real32)WINDOW_HEIGHT;
      real32 levelWidth = (real32)WINDOW_WIDTH;

      // Ball hits top
      if(ballPosition.y <= 0.f){
	ballPosition.y = 0.f;
	dy *= -1;
      }

      // Ball hits bottom
      if(ballPosition.y + ballWidth >= levelHeight){
	ballPosition.y = levelHeight - ballWidth * .5f;
	dy *= -1;
      }
  
      // Ball leaves level
      if(ballPosition.x <= 0.f || ballPosition.x + ballWidth >= levelWidth)
	{
	  ballPosition.x = ballStartX;
	  ballPosition.y = ballStartY;
	  dx = ballSpeed;
	  dy = 0;
	}


      if(check_aabb(
		 paddlePositions[0].x, paddlePositions[0].y, paddlePositions[0].z,
		 paddleWidth / 2.f, paddleHeight / 2.f, .5f,
		 ballPosition.x, ballPosition.y, ballPosition.z,
		 ballWidth / 2.f, ballWidth / 2.f, .5f
		    ))
      {
	ballPosition.x = paddlePositions[0].x + paddleWidth;
	dx *= -1;
	dy = 0;
	std::cout << "LEFT PADDLE COLLISION";
	if(ballPosition.y + ballWidth * .5f
	   <= paddlePositions[0].y + paddleWidth * .33f)
	  {
	    dy = -dx;
	    std::cout << " UPPER";
	  }
	if(ballPosition.y + ballWidth * .5f
	   >= paddlePositions[0].y + paddleWidth * .66f)
	  {
	    dy = dx;
	    std::cout << " LOWER";
	  }
	std::cout << std::endl;
      }

      if(check_aabb(
		 paddlePositions[1].x, paddlePositions[1].y, paddlePositions[1].z,
		 paddleWidth / 2.f, paddleHeight / 2.f, .5f,
		 ballPosition.x, ballPosition.y, ballPosition.z,
		 ballWidth / 2.f, ballWidth / 2.f, .5f
		    ))
	{
	  ballPosition.x = paddlePositions[1].x - ballWidth;
	  dx *= -1;
	  dy = 0;
	  if(ballPosition.y + ballWidth * .5f
	     <= paddlePositions[1].y + paddleHeight * .33f)
	    {
	      dy = dx;
	    }
	  if(ballPosition.y
	     >= paddlePositions[1].y + paddleHeight * .66f)
	    {
	      dy = -dx;
	    }
	}
      int32 mx, my;
      SDL_GetMouseState(&mx, &my);
      ballPosition.x =0.f;//+= dx * dt;
      ballPosition.y =0.f;//+= dy * dt;
      
      model = glm::mat4(1.f);
      model = glm::translate(model, ballPosition);
      model = glm::scale(model,
			 glm::vec3(ballWidth, ballWidth, ballWidth));

      setMat4(lampShader, "model", model); 
      glDrawArrays(GL_TRIANGLES, 0, 6);
      
      // NOTE(l4v): Unbind VAO
      glBindVertexArray(0);
      
      // NOTE(l4v): Swap the buffers
      SDL_GL_SwapWindow(window);      
    }

  // Destroy window
  SDL_DestroyWindow(window);
  window = 0;
  
  glDeleteVertexArrays(1, &paddleVAO);
  glDeleteVertexArrays(1, &lightVAO);
  glDeleteBuffers(1, &paddleVBO);

  SDL_Quit();
  
  return 0;

}
