#include <Board.hpp>

#include <algorithm>


void Board::register_to_board(Coordinates coord)
{
  m_board_array[coord.y][coord.x] = 1;
}

unsigned Board::get_cell_value(Coordinates coord)
{
  return m_board_array[coord.y][coord.x];
}

std::vector<Coordinates> Board::get_occupied_fields()
{
  std::vector<Coordinates> coords;
  for(int x = 0; x < m_board_array.size(); ++x)
  {
    for(int y = 0; y < m_board_array[x].size(); ++y)
    {
      if(m_board_array[x][y] == 1)
      {
        coords.push_back(Coordinates(y,x));
      }
    }
  }
  return coords;
}

void Board::check_for_completed_lines()
{
  for(auto& row : m_board_array)
  {
    if(GRID_WIDTH == std::count(row.begin(), row.end(), 1))
    {
      std::replace(row.begin(), row.end(), 1, 0);
    }
  }
}
