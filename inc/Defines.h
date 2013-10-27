#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#include <exception>
#include <string>

const int NUMBER_OF_KEYS = 323;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float STARTING_SPEED = 500.0;
const float INPUT_SPEED = 100.0;

const int BASE_SCORE_PER_LINE = 10;

const int GRID_WIDTH  = 10;
const int GRID_HEIGHT = 18;
const int GRID_UNIT = 30;
/** Squares are 30*30p **/
/** Board is 10*18 squares, which falls 2 short of standard, but whacchagonnado **/

const std::size_t HISCORE_TABLE_MAX_SIZE = 10;

const std::string SQUARE_IMG("pix/square.bmp");
const std::string BACKGROUND_IMG("pix/background.bmp");

const std::string TITLE("AWESOME TITLE");

const std::string HI_SCORE_FILE("HiScores.hst");

class GameOver {  };

class AbruptExit {  };

struct Coordinates
{
  Coordinates() : x(0), y(0) {}
  Coordinates(int a, int b) : x(a), y(b) {}

  Coordinates operator+(Coordinates other) const { return (Coordinates(x + other.x, y + other.y)); }
  int x;
  int y;
};

#endif // DEFINES_H_INCLUDED
