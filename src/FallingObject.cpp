#include "FallingObject.hpp"

void FallingObject::set_bounds(SDL_Surface* screen, SDL_Surface* square)
{
  m_bounds.left  = screen->w/2 - square->w * (GRID_WIDTH/2);
  m_bounds.right = screen->w/2 + square->w * (GRID_WIDTH/2);
  m_bounds.upper = square->h;
  m_bounds.lower = square->h * (GRID_HEIGHT+1);

  //set to corner
  m_currpos.x = m_bounds.left;
  m_currpos.y = m_bounds.upper;
}

void FallingObject::move_obj_left()
{
  ///CHECK FOR WALLS & BOUNDRIES

  if(m_currpos.x - GRID_UNIT >= m_bounds.left) m_currpos.x -= GRID_UNIT;
}

void FallingObject::move_obj_right()
{
  ///CHECK FOR WALLS & BOUNDRIES

  if(m_currpos.x + GRID_UNIT < m_bounds.right) m_currpos.x += GRID_UNIT;
}

void FallingObject::move_obj_up()
{
  ///ROTATE

  if(m_currpos.y - GRID_UNIT >= m_bounds.upper) m_currpos.y -= GRID_UNIT;
}

void FallingObject::move_obj_down()
{
  ///CHECK FOR BOTTOM

  if(m_currpos.y + GRID_UNIT < m_bounds.lower) m_currpos.y += GRID_UNIT;
}
