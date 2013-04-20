#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include <vector>

#include "Defines.h"

class Board
{
public:
  Board() : m_board_array(GRID_HEIGHT, std::vector<unsigned>(GRID_WIDTH)) {}

  void register_squares_to_board(std::vector<Coordinates> coords);
  unsigned get_cell_value(Coordinates coord);
  std::vector<Coordinates> get_occupied_fields();
  void check_for_completed_lines();   ///can be private, if called only from register_object

private:
  void rearrange_rows();

  std::vector<std::vector<unsigned>> m_board_array;
};

#endif // BOARD_HPP_INCLUDED