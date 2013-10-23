#ifndef DRAWER_HPP_INCLUDED
#define DRAWER_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <vector>

#include "Defines.h"

class Drawer
{
public:
  Drawer() : m_screen(0)
           , m_square(0)
           , m_text_surface(0)
           , m_gameover_text(0)
          {}
  ~Drawer()
  {
    TTF_CloseFont(m_font);
    SDL_FreeSurface(m_text_surface);
    SDL_FreeSurface(m_gameover_text);
    SDL_FreeSurface(m_background);
    SDL_FreeSurface(m_square);
    SDL_Quit();
  }

  int initialize();

  void draw_all(const std::vector<Coordinates>& object_coords,
                const std::vector<Coordinates>& board_coords,
                const unsigned long score,
                const unsigned level);

  void draw_gameover(const std::vector<Coordinates>& object_coords,
                     const std::vector<Coordinates>& board_coords,
                     const unsigned long score,
                     const unsigned level);

private:
  void calculate_block_position(const Coordinates& coord);
  void draw_squares_to(const std::vector<Coordinates>& coords);
  void draw_score_board(const unsigned long score, const unsigned level);

  SDL_Surface*   m_screen;
  SDL_Surface*   m_background;
  SDL_Surface*   m_square;
  SDL_Rect       m_game_area_rim;
  SDL_Rect       m_game_area;

  TTF_Font*      m_font;
  SDL_Color      m_text_color;
  SDL_Color      m_text_background;
  SDL_Surface*   m_text_surface;
  SDL_Rect       m_score_dest;
  SDL_Rect       m_level_dest;
  SDL_Rect       m_scoreboard_dest;

  SDL_Rect       m_objpos;

  SDL_Surface*   m_gameover_text;
  SDL_Rect       m_gameover_sign_dest;
};


#endif // DRAWER_HPP_INCLUDED
