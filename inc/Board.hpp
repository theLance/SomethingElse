#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include <vector>

#include "Defines.h"
#include "Score.hpp"

class Board
{
public:
  Board(Score& score) : m_score_board(score)
                      , m_board_array(GRID_HEIGHT, std::vector<unsigned>(GRID_WIDTH))
                      {}

  void register_squares_to_board(const std::vector<Coordinates>& coords);
  unsigned get_cell_value(const Coordinates& coord);
  std::vector<Coordinates> get_occupied_fields();

private:
  void check_for_completed_lines();   ///can be private, if called only from register_object
  void rearrange_rows();

  Score& m_score_board;

  std::vector<std::vector<unsigned>> m_board_array;
};

#endif // BOARD_HPP_INCLUDED
