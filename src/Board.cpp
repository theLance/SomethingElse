#include <Board.hpp>

#include <algorithm>


void Board::register_squares_to_board(const std::vector<Coordinates>& coords)
{
  std::for_each(coords.begin(), coords.end(),
                [&](Coordinates coord){m_board_array[coord.y][coord.x] = 1;});
  check_for_completed_lines();
}

unsigned Board::get_cell_value(const Coordinates& coord)
{
  return m_board_array[coord.y][coord.x];
}

std::vector<Coordinates> Board::get_occupied_fields()
{
  std::vector<Coordinates> coords;
  for(unsigned x = 0; x < m_board_array.size(); ++x)
  {
    for(unsigned y = 0; y < m_board_array[x].size(); ++y)
    {
      if(m_board_array[x][y] == 1)
      {
        coords.push_back(Coordinates(y,x));
      }
    }
  }
  return coords;
}

void Board::rearrange_rows()
{
  auto row = m_board_array.begin();
  while(row != m_board_array.end() && 0 == std::count(row->begin(), row->end(), 1))
  {
    ++row;
  }

  auto first_unempty_line = row;

  while(++row != m_board_array.end())
  {
    if(std::count(row->begin(), row->end(), 1) == 0)
    {
      auto temp_row = row;
      while(temp_row != first_unempty_line)
      {
        temp_row->swap(*(temp_row-1));
        temp_row--;
      }
      first_unempty_line++;
    }
  }
}

void Board::check_for_completed_lines()
{
  unsigned lines_cleared = 0;
  for(auto& row : m_board_array)
  {
    if(GRID_WIDTH == std::count(row.begin(), row.end(), 1))
    {
      std::replace(row.begin(), row.end(), 1, 0);
      ++lines_cleared;
    }
  }

  if(lines_cleared)
  {
    m_score_board.update_score(lines_cleared);
    rearrange_rows();
  }
}
