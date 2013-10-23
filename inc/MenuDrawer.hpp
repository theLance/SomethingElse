#ifndef MENUDRAWER_HPP_INCLUDED
#define MENUDRAWER_HPP_INCLUDED

#include <map>
#include <string>
#include <memory>

class SDL_Surface;
class SDL_Rect;

class MenuDrawer
{
public:
  MenuDrawer();
  void draw(unsigned current_choice);

private:
  void draw_option(SDL_Rect& prev_rect, unsigned option, unsigned current_choice);

  std::shared_ptr<SDL_Surface>  m_text_surface;

  std::shared_ptr<SDL_Surface>  m_title_text;
  std::shared_ptr<SDL_Rect>     m_title_dest;

  std::map<unsigned, std::string> m_options_text_map;
  std::shared_ptr<SDL_Surface>  m_option_text;
};


#endif // MENUDRAWER_HPP_INCLUDED
