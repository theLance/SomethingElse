#ifndef FALLINGOBJECT_HPP_INCLUDED
#define FALLINGOBJECT_HPP_INCLUDED

#include <SDL/SDL.h>

#include "Board.hpp"


class FallingObject
{
public:
  FallingObject(Board& board) : m_board(board) {}
  std::vector<Coordinates> get_coordinates();
  void reset_object();

  void rotate_object();
  void move_obj_down();
  void move_obj_left();
  void move_obj_right();

private:
  bool check_if_move_possible(const Coordinates& dest_coord);
  std::vector<Coordinates> rotate();

  Coordinates               m_center_coord;
  std::vector<Coordinates>  m_coordinates;
  Board&                    m_board;
};


#endif // FALLINGOBJECT_HPP_INCLUDED
