#include <cstdlib>
#include <iostream>
#include <sys/mman.h>
#include <new>
#include <string>
#include <sstream>

// TODO(l4v): Use our own or a C library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <x86intrin.h>

#include "SDL2/SDL.h"
#include "GL/glew.h"

// NOTE(l4v): For debugging, if the expression is false, an attempt
// is made to write to the 0 pointer, which automatically causes
// a crash.
#if PONG_SLOW
#define Assert(Expression) if(!(Expression)) {*(int*)0 = 0;}
#else
#define Assert(Expression)
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define internal static
#define global_variable static
#define local_persist static

#define Kibibytes(Value) ((Value)*1024LL)
#define Mebibytes(Value) (Kibibytes(Value)*1024LL)
#define Gibibytes(Value) (Mebibytes(Value)*1024LL)

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;

// paddle player, ai;
// ball b;


// TODO(l4v): Use the memory

// TODO(l4v): Do all these belong here?
struct camera_struct{
  glm::vec3 pos;
  glm::vec3 front;
  glm::vec3 up;
  
  real32 speed;
  real32 fov;
};

struct paddle{
  //  sf::Sprite sprite;
  real32 dy = 1.f;
  glm::vec3 position;
  real32 width;
  real32 height;
};

struct ball{
  real32 dx;
  real32 dy;
  glm::vec3 position;
  real32 width;
};
struct game_state{
  bool32 isInitialized;
  paddle player;
  paddle ai;
  ball b;
};

struct game_memory{
  bool32 isInitialized;

  uint64 PermanentStorageSize;
  void* PermanentStorage;

  uint64 TransientStorageSize;
  void* TransientStorage;
};

// TEMP
real32 paddleSpeed = 600.f;
real32 maxBallSpeed = 500.f;
real32 ballAccel = 10.f;

enum shader_type
  {
   VERTEX = 0,
   FRAGMENT
  };

enum last_scored
  {
   PLAYER_ONE = 1,
   PLAYER_TWO = -1
  };

internal inline bool check_aabb(real32, real32, real32,
				real32, real32, real32,
				real32, real32, real32,
				real32, real32, real32);

internal glm::mat4 look_at(glm::vec3, glm::vec3, glm::vec3);
internal const char* load_shader(const char*);
internal void check_shader_compilation(uint32, shader_type);
internal void check_shader_program_link(uint32);

internal uint32 load_texture(const char*);

internal inline void setVec3(uint32, const char*, const glm::vec3&);
internal inline void setVec3(uint32, const char*, real32, real32, real32);
internal inline void setMat4(uint32, const char*, const glm::mat4&);
internal inline void setFloat(uint32, const char*, real32);
internal inline void setInt(uint32, const char*, uint32);
internal inline void setInt(uint32, const char*, int32);
//void RenderAndUpdate(sf::RenderWindow*, const real32&);
//bool32 CheckCollision(real32, real32, real32, real32,
//		    real32, real32, real32, real32);
