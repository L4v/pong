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

const char* fragmentShaderSource = load_shader("cube.fs");
const char* vertexShaderSource = load_shader("cube.vs");
const char* lightFragmentShaderSource = load_shader("light.fs");
const char* lightVertexShaderSource = load_shader("light.vs");

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
  		       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.f, 0.f, -1.f,
  		       0.5f,  -0.5f, -0.5f,  1.0f, 0.0f, 0.f, 0.f, -1.f,
  		       0.5f,   0.5f, -0.5f,  1.0f, 1.0f, 0.f, 0.f, -1.f,
  		       0.5f,   0.5f, -0.5f,  1.0f, 1.0f, 0.f, 0.f, -1.f,
  		       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.f, 0.f, -1.f,
  		       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.f, 0.f, -1.f,

  		       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.f, 0.f, 1.f,
  		       0.5f,  -0.5f,  0.5f,  1.0f, 0.0f, 0.f, 0.f, 1.f,
  		       0.5f,   0.5f,  0.5f,  1.0f, 1.0f, 0.f, 0.f, 1.f,
  		       0.5f,   0.5f,  0.5f,  1.0f, 1.0f, 0.f, 0.f, 1.f,
  		       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.f, 0.f, 1.f,
  		       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.f, 0.f, 1.f,

  		       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.f, 0.f, 0.f,
  		       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.f, 0.f, 0.f,
  		       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.f, 0.f, 0.f,
  		       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.f, 0.f, 0.f,
  		       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.f, 0.f, 0.f,
  		       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.f, 0.f, 0.f,

  		       0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.f, 0.f, 0.f,
  		       0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.f, 0.f, 0.f,
  		       0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.f, 0.f, 0.f,
  		       0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.f, 0.f, 0.f,
  		       0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.f, 0.f, 0.f,
  		       0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.f, 0.f, 0.f,

  		       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.f, -1.f, 0.f,
  		       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,	 0.f, -1.f, 0.f,
  		       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	 0.f, -1.f, 0.f,
  		       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	 0.f, -1.f, 0.f,
  		       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.f, -1.f, 0.f,
  		       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.f, -1.f, 0.f,

  		       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.f, 1.f, 0.f,
  		       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	 0.f, 1.f, 0.f,
  		       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	 0.f, 1.f, 0.f,
  		       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	 0.f, 1.f, 0.f,
  		       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.f, 1.f, 0.f,
  		       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.f, 1.f, 0.f
  };
  
  // NOTE(l4v): Positions of 10 cubes
  
  glm::vec3 cubePositions[] = {
			       glm::vec3( 0.0f,  0.0f,  0.0f)
  };

  // NOTE(l4v): Vertex shaders
  // -------------------------
  uint32 vertexShader, lightVertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  lightVertexShader = glCreateShader(GL_VERTEX_SHADER);
  
  // NOTE(l4v): Attaching shader source code to the shader object
  glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
  glShaderSource(lightVertexShader, 1, &lightVertexShaderSource, 0);
  
  glCompileShader(vertexShader);
  check_shader_compilation(vertexShader, VERTEX);

  glCompileShader(lightVertexShader);
  check_shader_compilation(lightVertexShader, VERTEX);

  // NOTE(l4v): Fragment shaders
  // ---------------------------
  uint32 fragmentShader, lightFragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  lightFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
  glShaderSource(lightFragmentShader, 1, &lightFragmentShaderSource, 0);
  
  glCompileShader(fragmentShader);
  check_shader_compilation(fragmentShader, FRAGMENT);
  
  glCompileShader(lightFragmentShader);
  check_shader_compilation(lightFragmentShader, FRAGMENT);

  // NOTE(l4v): Creating a shader program object
  uint32 lightingShader, lampShader;
  lightingShader = glCreateProgram();
  glAttachShader(lightingShader, vertexShader);
  glAttachShader(lightingShader, fragmentShader);
  glLinkProgram(lightingShader);
  check_shader_program_link(lightingShader);
  
  lampShader = glCreateProgram();
  glAttachShader(lampShader, lightVertexShader);
  glAttachShader(lampShader, lightFragmentShader);
  glLinkProgram(lampShader);
  check_shader_program_link(lampShader);
  
  // NOTE(l4v): Deleting objects since they're not required after linking them
  // to the shader program
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glDeleteShader(lightVertexShader);
  glDeleteShader(lightFragmentShader);

  // NOTE(l4v): Creating the element buffer object, EBO
  uint32 VBO, VAO, lightVAO, lightVBO;
  
  // NOTE(l4v): Generating a VAO
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // NOTE(l4v): Telling OpenGL how to interpret the vertex data in memory

  // NOTE(l4v): Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // NOTE(l4v): Texture coords
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // NOTE(l4v): Normal
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*) (5 * sizeof(float)));
  glEnableVertexAttribArray(2);
  
  glGenVertexArrays(1, &lightVAO);
  
  glBindVertexArray(lightVAO);
  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);  

  // NOTE(l4v): Diffuse map
  // --------------------
  
  // NOTE(l4v): Binding the texture
  uint32 diffuseMap, specularMap;
  glGenTextures(1, &diffuseMap);
  glBindTexture(GL_TEXTURE_2D, diffuseMap);

  // NOTE(l4v): Tell stb to flip image on y-axis
  stbi_set_flip_vertically_on_load(true);
  
  // NOTE(l4v): Set wrapping and filtering options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  // NOTE(l4v): Loading and generating the actual texture
  // Texture variables
  int32 width, height, nChannels;
  // TODO(l4v): Make use of memory arenas
  uint8 *data;

  // NOTE(l4v): Loading first image
  data = stbi_load("container2.png", &width, &height, &nChannels, 0);
  if(data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
  else
    {
      std::cout << "ERROR::TEXTURE:FAILED_TO_LOAD_DIFFUSE_MAP" << std::endl;
    }
  // NOTE(l4v): Frees the image data
  stbi_image_free(data);

  // NOTE(l4v): Specular map
  // -----------------------
  glGenTextures(1, &specularMap);
  glBindTexture(GL_TEXTURE_2D, specularMap);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  data = stbi_load("container2_specular.png", &width, &height, &nChannels, 0);
  if(data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
  else
    {
      std::cout << "ERROR::TEXTURE:FAILED_TO_LOAD_SPECULAR_MAP" << std::endl;
    }

  stbi_image_free(data);
  
  glUseProgram(lightingShader);
  setInt(lightingShader, "material.diffuse", 0);
  setInt(lightingShader, "material.specular", 1);

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
  camera_struct camera;
  glm::mat4 model = glm::mat4(1.f);
  glm::mat4 projection;
  glm::mat4 view = glm::mat4(1.f);
  
  camera.pos   = glm::vec3(0.0f, 0.0f,  3.0f);
  camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
  camera.up    = glm::vec3(0.0f, 1.0f,  0.0f);
  camera.speed = 0.5f;

  // NOTE(l4v): Colors
  glm::vec3 objectColor = glm::vec3(1.f, 0.5f, 0.31f);
  glm::vec3 lightColor = glm::vec3(1.f, 1.f, 1.f);
  
  glm::vec3 lightPos(1.2f, 1.f, 2.f);

  real32 mouseSensitivity = 0.5f;
  real32 pitch = 0.f;
  real32 yaw = -90.f;


  camera.fov = 45.f;

  // NOTE(l4v): Radius of the rotating light source
  real32 radius = 2.f;

  // NOTE(l4v): Init materials and light
  // ----------------------------------
  setVec3(lightingShader, "material.ambient", 1.f, 0.5f, 0.31f);
  setVec3(lightingShader, "material.diffuse", 1.f, 0.5f, 0.31f);
  setVec3(lightingShader, "material.specular", 0.5f, 0.5f, 0.5f);
  setFloat(lightingShader, "material.shininess", 32.f);

  setVec3(lightingShader, "light.ambient", .2f, .2f, .2f);
  setVec3(lightingShader, "light.diffuse", .5f, .5f, .5f);
  setVec3(lightingShader, "light.specular", 1.f, 1.f, 1.f);

  while(!quit)
    {
      // NOTE(l4v): Gets the delta time
      now = SDL_GetPerformanceCounter();
      dt = ((real64)((now - last))) / SDL_GetPerformanceFrequency();
      last = now;

      // NOTE(l4v): Set camera speed
      camera.speed = 2.5f * dt;

      // TODO(l4v): MEMORY!!!
      const uint8* keystates;
      keystates = SDL_GetKeyboardState(0);

      // NOTE(l4v): Keyboard input irrelevant of events
      if(keystates[SDL_SCANCODE_W])
	camera.pos += camera.speed * camera.front;
      if(keystates[SDL_SCANCODE_S])
	camera.pos -= camera.speed * camera.front;
      if(keystates[SDL_SCANCODE_A])
	camera.pos -= glm::normalize(glm::cross(camera.front,
						camera.up))
	  * camera.speed;
      if(keystates[SDL_SCANCODE_D])
	camera.pos += glm::normalize(glm::cross(camera.front,
						camera.up))
	  * camera.speed;

      // NOTE(l4v): Keeps the camera on xy plane
      //      camera.pos.y = 0.f;
      
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
      projection = glm::perspective(glm::radians(camera.fov),
				    (real32) WINDOW_WIDTH / (real32) WINDOW_HEIGHT, 0.1f, 100.0f);
      
      // NOTE(l4v): Sets the world view
      view = look_at(
			 camera.pos,
			 camera.pos + camera.front,
			 camera.up
			 );
      
      // NOTE(l4v): Set background to black color
      glClearColor(0.2f, 0.3f, 0.3f, 1.f);
      
      // NOTE(l4v): Clear the color buffer
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      // NOTE(l4v): Cube
      // ---------------
      
      // NOTE(l4v): Lighting
      glUseProgram(lightingShader);
      
      setMat4(lightingShader, "model", model);
      setMat4(lightingShader, "view", view);
      setMat4(lightingShader, "projection", projection);
      setVec3(lightingShader, "objectColor", objectColor);
      setVec3(lightingShader, "lightColor", lightColor);
      setVec3(lightingShader, "light.position", lightPos);
      setVec3(lightingShader, "viewPos", camera.pos);

      
      // NOTE(l4v): Setting active texture unit and bind texture
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, specularMap);
      
      // NOTE(l4v): Draw cube
      glm::mat4 model = glm::mat4(1.f);
      model = glm::translate(model, cubePositions[0]);
      model = glm::rotate(model, glm::radians(0.f),
			  glm::vec3(1.f, 0.3f, 0.5f));
      setMat4(lightingShader, "model", model);

      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      // NOTE(l4v): Lamp
      // ----------------
      glUseProgram(lampShader);
      glBindVertexArray(lightVAO);

      lightPos = glm::vec3(radius * cos(glm::radians((real32)SDL_GetTicks() / 100.f)),
			   0.f,
			   radius * sin(glm::radians((real32)SDL_GetTicks() / 100.f)));
      
      model = glm::mat4(1.f);
      model = glm::translate(model, lightPos);
      model = glm::scale(model, glm::vec3(0.2f));
      
      setMat4(lampShader, "model", model);
      setMat4(lampShader, "view", view);
      setMat4(lampShader, "projection", projection);
      setVec3(lampShader, "objectColor", objectColor);
      setVec3(lampShader, "lightColor", lightColor);

      glDrawArrays(GL_TRIANGLES, 0, 36);
      
      // Note(l4v): Swap the buffers
      SDL_GL_SwapWindow(window);      
    }

  // Destroy window
  SDL_DestroyWindow(window);
  window = 0;
  
  glDeleteVertexArrays(1, &VAO);
  glDeleteVertexArrays(1, &lightVAO);
  glDeleteBuffers(1, &VBO);

  SDL_Quit();
  
  return 0;

}
