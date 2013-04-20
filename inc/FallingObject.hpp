#ifndef FALLINGOBJECT_HPP_INCLUDED
#define FALLINGOBJECT_HPP_INCLUDED

#include "SDL/SDL.h"

#include "Defines.h"

struct Coordinates
{
  Coordinates() : x(0), y(0) {}
  int x;
  int y;
};

class FallingObject
{
public:
  Coordinates get_coordinates() { return m_coordinates; }
  void reset_object();

  void move_obj_up();
  void move_obj_down();
  void move_obj_left();
  void move_obj_right();

private:
  Coordinates m_coordinates;
};

#endif // FALLINGOBJECT_HPP_INCLUDED
