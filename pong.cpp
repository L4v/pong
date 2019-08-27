#include "pong.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

internal const char* LoadShader(const char* path)
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

internal glm::mat4 LookAt(glm::vec3 cameraPos, glm::vec3 targetPos,
			   glm::vec3 worldUp)
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

internal void CheckShaderCompilation(uint32 shader, shader_type type)
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

internal void CheckShaderLink(uint32 program)
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

internal uint32 LoadTexture(const char* path)
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

internal void InitializeArena(memory_arena* Arena, memory_index Size, uint8* Base)
{
  Arena->Size = Size;
  Arena->Base = Base;
  Arena->Used = 0;
}

#define PushStruct(Arena, type) (type*)PushStruct_(Arena, sizeof(type))
void* PushStruct_(memory_arena* Arena, memory_index Size)
{
  Assert((Arena->Used + Size) <= Arena->Size);
  void* Result = Arena->Base + Arena->Used;
  Arena->Used += Size;
  
  return Result;
}

internal inline void SetVec3(uint32 shader, const char* variable, const glm::vec3& value)
{
  glUniform3fv(glGetUniformLocation(shader, variable), 1, &value[0]);
}

internal inline void SetVec3(uint32 shader, const char* variable, real32 x, real32 y, real32 z)
{
  glUniform3f(glGetUniformLocation(shader, variable), x, y, z);
}

internal inline void SetFloat(uint32 shader, const char* variable, real32 fValue)
{
  glUniform1f(glGetUniformLocation(shader, variable), fValue);
}

internal inline void SetMat4(uint32 shader, const char* variable, const glm::mat4 &mat)
{
  glUniformMatrix4fv(glGetUniformLocation(shader, variable), 1, GL_FALSE, &mat[0][0]);
}

internal inline void SetInt(uint32 shader, const char* variable, uint32 uValue)
{
  glUniform1i(glGetUniformLocation(shader, variable), uValue);
}

internal inline void SetInt(uint32 shader, const char* variable, int32 iValue)
{
  glUniform1i(glGetUniformLocation(shader, variable), iValue);
}

internal inline bool CheckAABB(real32 x1, real32 y1, real32 z1,
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

int main(int argc, char* argv[]){
#if PONG_INTERNAL
  void *BaseAddress = (void *)Gibibytes(250);
#else
  void *BaseAddress = (void *)(0);
#endif

  const char* cubeFragmentShaderSource = LoadShader("cube.fs");
  const char* cubeVertexShaderSource = LoadShader("cube.vs");
  const char* lightFragmentShaderSource = LoadShader("light.fs");
  const char* lightVertexShaderSource = LoadShader("light.vs");
  const char* paddleFragmentShaderSource = LoadShader("paddle.fs");
  const char* paddleVertexShaderSource = LoadShader("paddle.vs");
  
  SDL_Window* window;
  SDL_GLContext glContext;
  SDL_Event sdlEvent;

  bool quit;
  
  // NOTE(l4v): For getting delta time
  real64 dt = 0.0;
  int64 now = 0;
  int64 last = 0;
  
  // NOTE(l4v): Allocating new memory and subdividing it into parts
  game_memory Memory{};
  Memory.PermanentStorageSize = Mebibytes(60);
  Memory.TransientStorageSize = Mebibytes(100);
  
  uint64 TotalStorageSize = Memory.PermanentStorageSize
    + Memory.TransientStorageSize;
  Memory.PermanentStorage = mmap(BaseAddress, TotalStorageSize,
  				     PROT_READ | PROT_WRITE,
  				     MAP_ANONYMOUS | MAP_PRIVATE,
  				     -1,
  				     0);
  Memory.TransientStorage = (uint8 *)(Memory.PermanentStorage)
    + Memory.PermanentStorageSize;
  
  // NOTE(l4v): Check if memory allocation failed 
  Assert(Memory.PermanentStorage);  
  Assert(Memory.TransientStorage);
  
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
		       -.5f, -.5f, 0.f, 0.0f, 1.0f, // bottom left
		       -.5f, .5f, 0.f, 1.0f, 0.0f, // top left
		       .5f, .5f, 0.f, 0.0f, 0.0f,  // top right
		       .5f, -.5f, 0.f, 0.0f, 1.0f // bottom right
  };

  uint32 indices[] = {
		      0, 1, 2,
		      0, 2, 3
  };
  
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
  CheckShaderCompilation(lightVertexShader, VERTEX);

  glCompileShader(paddleVertexShader);
  CheckShaderCompilation(paddleVertexShader, VERTEX);

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
  CheckShaderCompilation(lightFragmentShader, FRAGMENT);

  glCompileShader(paddleFragmentShader);
  CheckShaderCompilation(paddleFragmentShader, FRAGMENT);

  // NOTE(l4v): Creating a shader program object
  uint32 lampShader, paddleShader;
  lampShader = glCreateProgram();
  glAttachShader(lampShader, lightVertexShader);
  glAttachShader(lampShader, lightFragmentShader);
  glLinkProgram(lampShader);
  CheckShaderLink(lampShader);

  paddleShader = glCreateProgram();
  glAttachShader(paddleShader, paddleVertexShader);
  glAttachShader(paddleShader, paddleFragmentShader);
  glLinkProgram(paddleShader);
  CheckShaderLink(paddleShader);
  
  // NOTE(l4v): Deleting objects since they're not required after linking them
  // to the shader program
  glDeleteShader(lightVertexShader);
  glDeleteShader(lightFragmentShader);
  glDeleteShader(paddleVertexShader);
  glDeleteShader(paddleFragmentShader);

  // NOTE(l4v): VAO, EBO, VBO...
  uint32
    lightVAO, lightVBO, lightEBO,
    paddleVBO, paddleVAO, paddleEBO;

  // NOTE(l4v): PADDLE
  // -----------------

  // NOTE(l4v): Generating a VAO
  glGenVertexArrays(1, &paddleVAO);
  glBindVertexArray(paddleVAO);
  glGenBuffers(1, &paddleVBO);
  glGenBuffers(1, &paddleEBO);

  glBindBuffer(GL_ARRAY_BUFFER, paddleVBO);

  // NOTE(l4v): Position data
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
	       GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(real32),
			(void*) 0);
  glEnableVertexAttribArray(0);

  // NOTE(l4v): EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, paddleEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
	       GL_DYNAMIC_DRAW);
  
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
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices,
	       GL_DYNAMIC_DRAW);

  // NOTE(l4v): Paddle texture
  uint32 paddleTex;
  paddleTex = LoadTexture("paddle.png");
  glUseProgram(paddleShader);
  SetInt(paddleShader, "tex", 0);

  // NOTE(l4v): Disable cursor
  SDL_ShowCursor(SDL_DISABLE);

  // NOTE(l4v): Capture the mouse
  SDL_CaptureMouse(SDL_TRUE);
  SDL_SetRelativeMouseMode(SDL_TRUE);

  // NOTE(l4v): Enables the z-buffer
  glEnable(GL_DEPTH_TEST);  

  // NOTE(l4v): Setting up the view
  glm::mat4 model = glm::mat4(1.f);
  glm::mat4 projection;
  glm::mat4 view = glm::mat4(1.f);

  // NOTE(l4v): Paddle and ball vars
  real32 paddleSpeed = 500.f;
  real32
    paddleWidth = 12.5f,
    paddleHeight = 75.f;
  real32 ballWidth = 10.f;
  real32 ballSpeed = 300.f;
  real32 dx = ballSpeed;
  real32 dy = 0.f;
  real32 paddleStartY1= (real32)WINDOW_HEIGHT * 0.5f;
  real32 paddleStartX1 = 50.f;
  real32 paddleStartY2 = (real32)WINDOW_HEIGHT * 0.5f;
  real32 paddleStartX2 = (real32)WINDOW_WIDTH - 50.f;
  real32 ballStartX = (real32)WINDOW_WIDTH * .5f;
  real32 ballStartY = (real32)WINDOW_HEIGHT * .5f;

  // NOTE(l4v): Used to determine who's time it is to scoren
  last_scored lastScored = PLAYER_ONE;
  uint32
    playerOneScore = 0,
    playerTwoScore = 0;
  bool justStarted = true;

  // NOTE(l4v): For getting delta time
  now = SDL_GetPerformanceCounter();
  last = now;
  dt = 0.f;
  while(!quit)
    {
      // NOTE(l4v): Setting up game memory
      Assert(sizeof(game_state) <= Memory.PermanentStorageSize);
      game_state* GameState = (game_state*)Memory.PermanentStorage;
      if(!Memory.IsInitialized)
	{
	  GameState->PlayerOne.position.x = paddleStartX1;
	  GameState->PlayerOne.position.y = paddleStartY1;
	  GameState->PlayerOne.position.z = 1;
	  GameState->PlayerTwo.position.x = paddleStartX2;
	  GameState->PlayerTwo.position.y = paddleStartY2;
	  GameState->PlayerTwo.position.z = 1;
	  GameState->Ball.position.x = ballStartX;
	  GameState->Ball.position.y = ballStartY;
	  GameState->Ball.position.z = 1;

	  Memory.IsInitialized++;
	}
      
      // NOTE(l4v): Gets the delta time
      now = SDL_GetPerformanceCounter();
      dt = ((real64)((now - last))) / SDL_GetPerformanceFrequency();
      last = now;

      // TODO(l4v): MEMORY!!!
      const uint8* keystates;
      keystates = SDL_GetKeyboardState(0);

      // NOTE(l4v): Keyboard input irrelevant of events
      if(keystates[SDL_SCANCODE_W])
	GameState->PlayerOne.position.y -= paddleSpeed * dt;
	
      if(keystates[SDL_SCANCODE_S])
	GameState->PlayerOne.position.y += paddleSpeed * dt;
      
      if(keystates[SDL_SCANCODE_UP])
	GameState->PlayerTwo.position.y -= paddleSpeed * dt;
	
      if(keystates[SDL_SCANCODE_DOWN])
	GameState->PlayerTwo.position.y += paddleSpeed * dt;
      
      if(keystates[SDL_SCANCODE_R])
	{
	  lastScored = PLAYER_ONE;
	  justStarted = true;

	  playerOneScore = 0;
	  playerTwoScore = 0;
	  
	  GameState->PlayerOne.position.y = paddleStartY1;
	  GameState->PlayerTwo.position.y = paddleStartY2;

	  GameState->Ball.position.x = ballStartX;
	  GameState->Ball.position.y = ballStartY;
	  dx = ballSpeed;
	  dy = 0.f;
	}

      // NOTE(l4v): Check that paddles don't leave the level
      if(GameState->PlayerOne.position.y - paddleHeight * .5f <= 0.f)
	GameState->PlayerOne.position.y = paddleHeight * .5f;
      if(GameState->PlayerOne.position.y + paddleHeight * .5f >= (real32)WINDOW_HEIGHT)
	GameState->PlayerOne.position.y = (real32)WINDOW_HEIGHT - paddleHeight * .5f;
      if(GameState->PlayerTwo.position.y - paddleHeight * .5f <= 0.f)
	GameState->PlayerTwo.position.y = paddleHeight * .5f;
      if(GameState->PlayerTwo.position.y + paddleHeight * .5f >= (real32)WINDOW_HEIGHT)
	GameState->PlayerTwo.position.y = (real32)WINDOW_HEIGHT - paddleHeight * .5f;
      
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
      projection = glm::ortho(.0f,
			      (real32)WINDOW_WIDTH,
			      (real32)WINDOW_HEIGHT,
			      0.f,
			      -1.f, 1.f);

      // NOTE(l4v): Set background to black color
      glClearColor(0.1f, 0.1f, 0.1f, 1.f);
      
      // NOTE(l4v): Clear the color buffer
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glUseProgram(paddleShader);
      SetMat4(paddleShader, "projection", projection);      

      // NOTE(l4v): Setting active texture unit and bind texture
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, paddleTex);

      // NOTE(l4v): Draw paddle
      glm::vec3* positions[2] = {
				 &GameState->PlayerOne.position,
				 &GameState->PlayerTwo.position
      };
      for(size_t i = 0; i < 2; ++i)
      	{
      	  glm::mat4 model = glm::mat4(1.f);
      	  model = glm::translate(model, *positions[i]);
      	  model = glm::scale(model,
      			     glm::vec3(paddleWidth, paddleHeight, 1.f));
      	  SetMat4(paddleShader, "model", model);

	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, paddleEBO);
	  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      	}
      
      // NOTE(l4v): Ball
      // ----------------
      glUseProgram(lampShader);
      SetMat4(lampShader, "projection", projection);

      real32 levelHeight = (real32)WINDOW_HEIGHT;
      real32 levelWidth = (real32)WINDOW_WIDTH;
      
      // Ball hits top
      if(GameState->Ball.position.y - ballWidth * .5f <= 0.f){
	GameState->Ball.position.y = ballWidth * .5f;
	dy *= -1;
      }

      // Ball hits bottom
      if(GameState->Ball.position.y + ballWidth * .5f >= levelHeight){
	GameState->Ball.position.y = levelHeight - ballWidth * .5f;
	dy *= -1;
      }
  
      // Ball leaves level
      if(GameState->Ball.position.x - ballWidth * .5f <= 0.f
	 || GameState->Ball.position.x + ballWidth * .5f >= levelWidth)
	{
	  GameState->Ball.position.x = ballStartX;
	  GameState->Ball.position.y = ballStartY;
	  dx = ballSpeed;
	  dy = 0;
	}


      // NOTE(l4v): Player 1 collision
      if(CheckAABB(
		 GameState->PlayerOne.position.x, GameState->PlayerOne.position.y, GameState->PlayerOne.position.z,
		 paddleWidth / 2.f, paddleHeight / 2.f, .5f,
		 GameState->Ball.position.x, GameState->Ball.position.y, GameState->Ball.position.z,
		 ballWidth / 2.f, ballWidth / 2.f, .5f
		    ))
      {
	GameState->Ball.position.x = GameState->PlayerOne.position.x + paddleWidth;
	dx *= -1;
	dy = 0;
	if(GameState->Ball.position.y
	   <= GameState->PlayerOne.position.y - paddleWidth * .33f)
	  {
	    dy = -dx;
	  }
	if(GameState->Ball.position.y
	   >= GameState->PlayerOne.position.y + paddleWidth * .33f)
	  {
	    dy = dx;
	  }
      }

      // NOTE(l4v): Player 2 collision
      if(CheckAABB(
		 GameState->PlayerTwo.position.x, GameState->PlayerTwo.position.y, GameState->PlayerTwo.position.z,
		 paddleWidth / 2.f, paddleHeight / 2.f, .5f,
		 GameState->Ball.position.x, GameState->Ball.position.y, GameState->Ball.position.z,
		 ballWidth / 2.f, ballWidth / 2.f, .5f
		    ))
	{
	  GameState->Ball.position.x = GameState->PlayerTwo.position.x - ballWidth;
	  dx *= -1;
	  dy = 0;
	  if(GameState->Ball.position.y
	     <= GameState->PlayerTwo.position.y - paddleHeight * .33f)
	    {
	      dy = dx;
	    }
	  if(GameState->Ball.position.y
	     >= GameState->PlayerTwo.position.y + paddleHeight * .33f)
	    {
	      dy = -dx;
	    }
	}
      GameState->Ball.position.x += dx * dt;
      GameState->Ball.position.y += dy * dt;
      
      model = glm::mat4(1.f);
      model = glm::translate(model, GameState->Ball.position);
      model = glm::scale(model,
			 glm::vec3(ballWidth, ballWidth, ballWidth));
      SetMat4(lampShader, "model", model); 

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, paddleEBO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      
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

  munmap(Memory.PermanentStorage, Memory.PermanentStorageSize);
  munmap(Memory.TransientStorage, Memory.TransientStorageSize);
  
  return 0;

}
https://youtu.be/IJYTwhqfKLg?t=3239
