#ifndef DRAWER_HPP_INCLUDED
#define DRAWER_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <iostream>
#include <vector>
#include <sstream>

#include "Defines.h"
#include "FallingObject.hpp"


class Drawer
{
public:
  Drawer(FallingObject& fallobj, Board& board, Score& scoreboard) : WINDOW_WIDTH(WIDTH)
                                                                  , WINDOW_HEIGHT(HEIGHT)
                                                                  , m_screen(0)
                                                                  , m_square(0)
                                                                  , m_text_surface(0)
                                                                  , m_gameover_text(0)
                                                                  , m_fallobj(fallobj)
                                                                  , m_board(board)
                                                                  , m_score_board(scoreboard)
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

  void draw_all();

  void draw_gameover();

private:
  void calculate_block_position(const Coordinates& coord);
  void draw_squares_to(const std::vector<Coordinates>& coords);
  void draw_score_board();

  const int      WINDOW_WIDTH;
  const int      WINDOW_HEIGHT;
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

  FallingObject& m_fallobj;
  Board&         m_board;
  Score&         m_score_board;
};


#endif // DRAWER_HPP_INCLUDED
