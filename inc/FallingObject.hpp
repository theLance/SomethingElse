#ifndef FALLINGOBJECT_HPP_INCLUDED
#define FALLINGOBJECT_HPP_INCLUDED

#include "SDL/SDL.h"

#include "Defines.h"

class FallingObject
{
  struct Boundries
  {
    int left;
    int right;
    int upper;
    int lower;
  };

public:
  SDL_Rect* get_current_position() { return &m_currpos; }

  void set_bounds(SDL_Surface* screen, SDL_Surface* square);
  Boundries get_bounds() { return m_bounds; }

  void move_obj_up();
  void move_obj_down();
  void move_obj_left();
  void move_obj_right();

private:
  SDL_Rect  m_currpos;
  Boundries m_bounds;
};

#endif // FALLINGOBJECT_HPP_INCLUDED
