#include "FallingObject.hpp"


void FallingObject::reset_object()
{
  //spawn to center top
  m_coordinates.x = GRID_WIDTH / 2;
  m_coordinates.y = 0;
}
void FallingObject::move_obj_left()
{
  ///CHECK FOR WALLS & BOUNDRIES

  if(m_coordinates.x - 1 >= 0) m_coordinates.x--;
}

void FallingObject::move_obj_right()
{
  ///CHECK FOR WALLS & BOUNDRIES

  if(m_coordinates.x + 1 < GRID_WIDTH) m_coordinates.x++;
}

void FallingObject::move_obj_up()
{
  ///ROTATE

  if(m_coordinates.y - 1 >= 0) m_coordinates.y--;
}

void FallingObject::move_obj_down()
{
  ///CHECK FOR BOTTOM

  if(m_coordinates.y + 1 < GRID_HEIGHT) m_coordinates.y++;
}
