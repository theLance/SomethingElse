#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#include <exception>

#define WIDTH  800
#define HEIGHT 600

#define STARTING_SPEED 500
#define INPUT_SPEED    100

#define BASE_SCORE_PER_LINE 10

#define GRID_WIDTH  10
#define GRID_HEIGHT 18
#define GRID_UNIT 30
/** Squares are 30*30p **/
/** Board is 10*18 squares, which falls 2 short of standard, but whacchagonnado **/

const std::size_t HISCORE_TABLE_MAX_SIZE = 10;

class GameOver {  };

struct Coordinates
{
  Coordinates() : x(0), y(0) {}
  Coordinates(int a, int b) : x(a), y(b) {}

  Coordinates operator+(Coordinates other) const { return (Coordinates(x + other.x, y + other.y)); }
  int x;
  int y;
};

#endif // DEFINES_H_INCLUDED
