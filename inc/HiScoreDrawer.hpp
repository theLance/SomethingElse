#ifndef HISCOREDRAWER_HPP_INCLUDED
#define HISCOREDRAWER_HPP_INCLUDED

#include <map>
#include <string>
#include <memory>

#include <HiScoreTable.hpp>

class SDL_Surface;
class SDL_Rect;


class HiScoreDrawer
{
public:
  HiScoreDrawer();
  void draw(const HiScoreTable::HiScoreTableMap& score_map);

private:
  void display_board(const HiScoreTable::HiScoreTableMap& score_map);

  std::shared_ptr<SDL_Surface>    m_title_text;
  std::shared_ptr<SDL_Rect>       m_title_dest;

  std::shared_ptr<SDL_Surface>    m_line_surface;
};

#endif // HISCOREDRAWER_HPP_INCLUDED
