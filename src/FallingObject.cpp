#include "FallingObject.hpp"
#include "ObjectCreator.hpp"

#include <algorithm>

std::vector<Coordinates> FallingObject::get_coordinates()
{
  std::vector<Coordinates> coords;
  for(auto coord : m_coordinates)
  {
    coords.push_back(Coordinates(coord.x + m_center_coord.x, coord.y + m_center_coord.y));
  }
  return coords;
}
void FallingObject::reset_object()
{
  m_center_coord.x = GRID_WIDTH / 2;
  m_center_coord.y = 1;

  //get random type
  m_coordinates = ObjectCreator::get_random_object();

  ///check if spawning possible (if not, game over)
  if(!check_if_move_possible(m_center_coord))
  {
    ///END GAME
    throw 2;
  }
}

bool FallingObject::check_if_move_possible(Coordinates dest_coord)
{
  for(auto coord : m_coordinates)
  {
    if( coord.x + dest_coord.x < 0 ||
        coord.x + dest_coord.x >= GRID_WIDTH ||
        coord.y + dest_coord.y >= GRID_HEIGHT )
    {
      return false;
    }
    if(m_board->get_cell_value(coord + dest_coord))
    {
      return false;
    }
  }

  return true;
}

void FallingObject::move_obj_left()
{
  if(check_if_move_possible( Coordinates(m_center_coord.x - 1, m_center_coord.y) ))
  {
    m_center_coord.x--;
  }
}

void FallingObject::move_obj_right()
{
  if(check_if_move_possible( Coordinates(m_center_coord.x + 1, m_center_coord.y) ))
  {
    m_center_coord.x++;
  }
}

std::vector<Coordinates> FallingObject::rotate()
{
  std::vector<Coordinates> rotated_obj;

  std::for_each(m_coordinates.begin(), m_coordinates.end(),
                [&](Coordinates coord){ rotated_obj.push_back(Coordinates(coord.y*-1, coord.x)); });

  return rotated_obj;
}

void FallingObject::rotate_object()
{
  std::vector<Coordinates> orig = m_coordinates;
  m_coordinates = rotate();
  if(!check_if_move_possible( m_center_coord ))
  {
    m_coordinates = orig;
  }
}

void FallingObject::move_obj_down()
{
  if(check_if_move_possible( Coordinates(m_center_coord.x, m_center_coord.y + 1) ))
  {
    m_center_coord.y++;
  }
  else
  {
    m_board->register_squares_to_board(get_coordinates());
    reset_object();
  }
}

