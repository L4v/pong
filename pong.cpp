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

  real32 paddleVertices[] = {
			     -.25f, -.5f, 0.f, // bottom left
			     -.25f, .5f, 0.f, // top left
			     .25f, -.5f, 0.f, // bottom right
			     .25f, .5f, 0.f // top right
  };

  uint32 indices[] = {
		      0, 1, 2,
		      1, 2, 3
  };
  
  // NOTE(l4v): Positions of cubes
  
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

  // NOTE(l4v): Positions of point lights
  glm::vec3 pointLightPositions[] = {
				     glm::vec3( 0.7f,  0.2f,  2.0f),
				     glm::vec3( 2.3f, -3.3f, -4.0f),
				     glm::vec3(-4.0f,  2.0f, -12.0f),
				     glm::vec3( 0.0f,  0.0f, -3.0f)
  };
  
  // NOTE(l4v): Vertex shaders
  // -------------------------
  uint32 cubeVertexShader, lightVertexShader, paddleVertexShader;
  cubeVertexShader = glCreateShader(GL_VERTEX_SHADER);
  lightVertexShader = glCreateShader(GL_VERTEX_SHADER);
  paddleVertexShader = glCreateShader(GL_VERTEX_SHADER);
  
  // NOTE(l4v): Attaching shader source code to the shader object
  glShaderSource(cubeVertexShader, 1, &cubeVertexShaderSource, 0);
  glShaderSource(lightVertexShader, 1, &lightVertexShaderSource, 0);
  glShaderSource(paddleVertexShader, 1, &paddleVertexShaderSource, 0);

  // NOTE(l4v): Shader compilation
  glCompileShader(cubeVertexShader);
  check_shader_compilation(cubeVertexShader, VERTEX);

  glCompileShader(lightVertexShader);
  check_shader_compilation(lightVertexShader, VERTEX);

  glCompileShader(paddleVertexShader);
  check_shader_compilation(paddleVertexShader, VERTEX);

  // NOTE(l4v): Fragment shaders
  // ---------------------------
  uint32 cubeFragmentShader, lightFragmentShader, paddleFragmentShader;
  cubeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  lightFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  paddleFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // NOTE(l4v): Attaching shader source code to shader object
  glShaderSource(cubeFragmentShader, 1, &cubeFragmentShaderSource, 0);
  glShaderSource(lightFragmentShader, 1, &lightFragmentShaderSource, 0);
  glShaderSource(paddleFragmentShader, 1, &paddleFragmentShaderSource, 0);

  // NOTE(l4v): Shader compilation
  glCompileShader(cubeFragmentShader);
  check_shader_compilation(cubeFragmentShader, FRAGMENT);
  
  glCompileShader(lightFragmentShader);
  check_shader_compilation(lightFragmentShader, FRAGMENT);

  glCompileShader(paddleFragmentShader);
  check_shader_compilation(paddleFragmentShader, FRAGMENT);

  // NOTE(l4v): Creating a shader program object
  uint32 lightingShader, lampShader, paddleShader;
  lightingShader = glCreateProgram();
  glAttachShader(lightingShader, cubeVertexShader);
  glAttachShader(lightingShader, cubeFragmentShader);
  glLinkProgram(lightingShader);
  check_shader_program_link(lightingShader);
  
  lampShader = glCreateProgram();
  glAttachShader(lampShader, lightVertexShader);
  glAttachShader(lampShader, lightFragmentShader);
  glLinkProgram(lampShader);
  check_shader_program_link(lampShader);

  paddleShader = glCreateProgram();
  glAttachShader(paddleShader, lightVertexShader);
  glAttachShader(paddleShader, lightFragmentShader);
  glLinkProgram(paddleShader);
  check_shader_program_link(paddleShader);
  
  // NOTE(l4v): Deleting objects since they're not required after linking them
  // to the shader program
  glDeleteShader(cubeVertexShader);
  glDeleteShader(cubeFragmentShader);
  glDeleteShader(lightVertexShader);
  glDeleteShader(lightFragmentShader);
  glDeleteShader(paddleVertexShader);
  glDeleteShader(paddleFragmentShader);

  // NOTE(l4v): VAO, EBO, VBO...
  uint32
    cubeVBO, cubeVAO,
    lightVAO, lightVBO,
    paddleVBO, paddleEBO, paddleVAO;

  // NOTE(l4v): CUBE
  // ---------------
  
  // NOTE(l4v): Generating a VAO
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &cubeVBO);
  glBindVertexArray(cubeVAO);
  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // NOTE(l4v): Position data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // NOTE(l4v): Texture coords data
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // NOTE(l4v): Normal data
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
			(void*) (5 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // NOTE(l4v): LAMP
  // ---------------

  // NOTE(l4v): Generating a VAO
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);
  
  // NOTE(l4v): Position data
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);  

  // NOTE(l4v): Loading texture maps
  uint32 diffuseMap, specularMap, emissionMap;
  diffuseMap = load_texture("container2.png");
  specularMap = load_texture("container2_specular.png");

  // NOTE(l4v): PADDLE
  // -----------------
  glGenVertexArrays(1, &paddleVAO);
  glGenBuffers(1, &paddleVBO);
  glGenBuffers(1, &paddleEBO);
  glBindVertexArray(paddleVAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, paddleVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(paddleVertices), paddleVertices, GL_DYNAMIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, paddleEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
  
  // NOTE(l4v): Position data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(real32), (void*)0);
  glEnableVertexAttribArray(0);
  
  glUseProgram(lightingShader);
  setInt(lightingShader, "material.diffuse", 0);
  setInt(lightingShader, "material.specular", 1);
  setInt(lightingShader, "material.emission", 2);

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
  
  glm::vec3 lightDir(-.2f, -1.f, -.3f);

  real32 mouseSensitivity = 0.5f;
  real32 pitch = 0.f;
  real32 yaw = -90.f;

  glm::vec3 lightPos = glm::vec3(1.f, 1.f, 1.f);

  camera.fov = 45.f;

  // NOTE(l4v): Radius of the rotating light source
  real32 radius = 2.f;

  // NOTE(l4v): Init materials and light
  // ----------------------------------
  setVec3(lightingShader, "material.ambient", 1.f, 0.5f, 0.31f);
  setVec3(lightingShader, "material.diffuse", 1.f, 0.5f, 0.31f);
  setVec3(lightingShader, "material.specular", 0.5f, 0.5f, 0.5f);
  setFloat(lightingShader, "material.shininess", 32.f);

  // NOTE(l4v): Directional light
  setVec3(lightingShader, "dirLight.direction", -.2f, -1.f, -.3f);
  setVec3(lightingShader, "dirLight.ambient", 0.05f, 0.05f, 0.05f);
  setVec3(lightingShader, "dirLight.diffuse", 0.4f, 0.4f, 0.4f);
  setVec3(lightingShader, "dirLight.specular", 0.5f, 0.5f, 0.5f);
  
  // NOTE(l4v): Point lights  
  setVec3(lightingShader, "pointLights[0].position",
	  pointLightPositions[0]);
  setVec3(lightingShader, "pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
  setVec3(lightingShader, "pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
  setVec3(lightingShader, "pointLights[0].specular", 1.0f, 1.0f, 1.0f);
  setFloat(lightingShader, "pointLights[0].constant", 1.f);
  setFloat(lightingShader, "pointLights[0].linear", .09f);
  setFloat(lightingShader, "pointLights[0].quadratic", .032f);
  
  setVec3(lightingShader, "pointLights[1].position",
	  pointLightPositions[1]);
  setVec3(lightingShader, "pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
  setVec3(lightingShader, "pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
  setVec3(lightingShader, "pointLights[1].specular", 1.0f, 1.0f, 1.0f);
  setFloat(lightingShader, "pointLights[1].constant", 1.f);
  setFloat(lightingShader, "pointLights[1].linear", .09f);
  setFloat(lightingShader, "pointLights[1].quadratic", .032f);
  
  setVec3(lightingShader, "pointLights[2].position",
	  pointLightPositions[2]);
  setVec3(lightingShader, "pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
  setVec3(lightingShader, "pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
  setVec3(lightingShader, "pointLights[2].specular", 1.0f, 1.0f, 1.0f);
  setFloat(lightingShader, "pointLights[2].constant", 1.f);
  setFloat(lightingShader, "pointLights[2].linear", .09f);
  setFloat(lightingShader, "pointLights[2].quadratic", .032f);

  setVec3(lightingShader, "pointLights[3].position",
	  pointLightPositions[3]);
  setVec3(lightingShader, "pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
  setVec3(lightingShader, "pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
  setVec3(lightingShader, "pointLights[3].specular", 1.0f, 1.0f, 1.0f);
  setFloat(lightingShader, "pointLights[3].constant", 1.f);
  setFloat(lightingShader, "pointLights[3].linear", .09f);
  setFloat(lightingShader, "pointLights[3].quadratic", .032f);
  
  // NOTE(l4v): Spotlight
  setVec3(lightingShader, "spotLight.ambient", 0.0f, 0.0f, 0.0f);
  setVec3(lightingShader, "spotLight.diffuse", 1.0f, 1.0f, 1.0f);
  setVec3(lightingShader, "spotLight.specular", 1.0f, 1.0f, 1.0f);
  setFloat(lightingShader, "spotLight.constant", 1.0f);
  setFloat(lightingShader, "spotLight.linear", 0.09);
  setFloat(lightingShader, "spotLight.quadratic", 0.032);
  setFloat(lightingShader, "spotLight.cutOff",
	   glm::cos(glm::radians(12.5f)));
  setFloat(lightingShader, "spotLight.outerCutOff",
	   glm::cos(glm::radians(15.0f)));  
  
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
      glClearColor(0.1f, 0.1f, 0.1f, 1.f);
      
      // NOTE(l4v): Clear the color buffer
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      // NOTE(l4v): Cube
      // ---------------
      
      // NOTE(l4v): Lighting
      glUseProgram(lightingShader);
      
      setMat4(lightingShader, "view", view);
      setMat4(lightingShader, "projection", projection);
      setVec3(lightingShader, "viewPos", camera.pos);
      setVec3(lightingShader, "spotLight.position", camera.pos);
      setVec3(lightingShader, "spotLight.direction", camera.front);
      
      
      // NOTE(l4v): Setting active texture unit and bind texture
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, diffuseMap);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, specularMap);
      
      // NOTE(l4v): Draw cube
      for(size_t i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); ++i)
	{
	  glm::mat4 model = glm::mat4(1.f);
	  model = glm::translate(model, cubePositions[i]);
	  float angle = 20.f * i;
	  model = glm::rotate(model, glm::radians(angle),
			      glm::vec3(1.f, 0.3f, 0.5f));
	  setMat4(lightingShader, "model", model);

	  glBindVertexArray(cubeVAO);
	  glDrawArrays(GL_TRIANGLES, 0, 36);
	}
      

      // NOTE(l4v): Lamp
      // ----------------
      glUseProgram(lampShader);
      glBindVertexArray(lightVAO);

      setMat4(lampShader, "view", view);
      setMat4(lampShader, "projection", projection);
      
      for(size_t i = 0; i < sizeof(pointLightPositions) / sizeof(glm::vec3);
	  ++i)
	{	 
	  model = glm::mat4(1.f);
	  model = glm::translate(model, pointLightPositions[i]);
	  model = glm::scale(model, glm::vec3(0.2f));

	  setMat4(lampShader, "model", model); 
	  glDrawArrays(GL_TRIANGLES, 0, 36);
	}

      // NOTE(l4v): Paddle
      // -----------------
      glUseProgram(paddleShader);
      glBindVertexArray(paddleVAO);

      setMat4(paddleShader, "view", view);
      setMat4(paddleShader, "projection", projection);

      model = glm::mat4(1.f);
      model = glm::translate(model, glm::vec3(5.f, 5.f, 5.f));

      setMat4(paddleShader, "model", model);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      
      // NOTE(l4v): Unbind VAO
      glBindVertexArray(0);
      
      // NOTE(l4v): Swap the buffers
      SDL_GL_SwapWindow(window);      
    }

  // Destroy window
  SDL_DestroyWindow(window);
  window = 0;
  
  glDeleteVertexArrays(1, &cubeVAO);
  glDeleteVertexArrays(1, &lightVAO);
  glDeleteBuffers(1, &cubeVBO);

  SDL_Quit();
  
  return 0;

}
