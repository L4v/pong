#include <cstdlib>
#include <iostream>
#include <sys/mman.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// For debugging, if the expression is false, an attempt
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

//struct game_data{
//sf::RenderWindow* window
//}

sf::RenderWindow window;

struct game_memory{
  bool32 isInitialized;

  uint64 PermanentStorageSize;
  void* PermanentStorage;

  uint64 TransientStorageSize;
  void* TransientStorage;
};

struct game_state{
  
};

struct paddle{
  sf::Sprite sprite;
  real32 dy = 1.f;
};

struct ball{
  sf::Sprite sprite;
  real32 dx;
  real32 dy;
  real32 x_dir;
  real32 y_dir;
};

//game_data data;

// TEMP
real32 paddleSpeed = 500.f;
real32 maxBallSpeed = 500.f;
real32 ballAccel = 10.f;

paddle player, ai;
ball b;

// struct paddle{
//     int x;
//     int y;
//     int width;
//     int height;
// };

void RenderAndUpdate(sf::RenderWindow*, const real32& dt);

