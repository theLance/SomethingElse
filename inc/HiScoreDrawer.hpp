#ifndef HISCOREDRAWER_HPP_INCLUDED
#define HISCOREDRAWER_HPP_INCLUDED

#include <vector>
#include <string>
#include <memory>

class SDL_Surface;
class SDL_Rect;

class HiScoreDrawer
{
public:
  HiScoreDrawer();
  void draw(const std::vector<std::string>& score_vector);

private:
  void display_board(const std::vector<std::string>& score_vector);

  std::shared_ptr<SDL_Surface>    m_title_text;
  std::shared_ptr<SDL_Rect>       m_title_dest;

  std::shared_ptr<SDL_Surface>    m_line_surface;
};

#endif // HISCOREDRAWER_HPP_INCLUDED
