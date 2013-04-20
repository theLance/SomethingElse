#include "FallingObject.hpp"


void FallingObject::reset_object()
{
  //get random type
  ///TODO

  //check if spawning possible (if not, game over)

  //spawn to center top
  m_coordinates.x = GRID_WIDTH / 2;
  m_coordinates.y = 0;
}

bool FallingObject::check_if_move_possible(Coordinates dest_coord)
{
  if( dest_coord.x < 0 || dest_coord.x >= GRID_WIDTH || dest_coord.y >= GRID_HEIGHT
     || dest_coord.y < 0) ///REMOVE THIS AFTER ROTATION IS IMPLEMENTED!!!
  {
    return false;
  }
  if(m_board->get_cell_value(dest_coord))
  {
    return false;
  }
  return true;
}

void FallingObject::move_obj_left()
{
  if(check_if_move_possible( Coordinates(m_coordinates.x - 1, m_coordinates.y) ))
  {
    m_coordinates.x--;
  }
}

void FallingObject::move_obj_right()
{
  if(check_if_move_possible( Coordinates(m_coordinates.x + 1, m_coordinates.y) ))
  {
    m_coordinates.x++;
  }
}

void FallingObject::move_obj_up()
{
  ///ROTATE !!!

  if(check_if_move_possible( Coordinates(m_coordinates.x, m_coordinates.y - 1) ))
  {
    m_coordinates.y--;
  }
}

void FallingObject::move_obj_down()
{
  if(check_if_move_possible( Coordinates(m_coordinates.x, m_coordinates.y + 1) ))
  {
    m_coordinates.y++;
  }
  else
  {
    m_board->register_to_board(m_coordinates);
    m_board->check_for_completed_lines();
    reset_object();
  }
}
