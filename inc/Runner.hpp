#ifndef RUNNER_HPP_INCLUDED
#define RUNNER_HPP_INCLUDED

#include <iostream>

#include "SDL/SDL_ttf.h"

#include "FallingObject.hpp"


class Runner
{
public:
  Runner() : WINDOW_WIDTH(WIDTH), WINDOW_HEIGHT(HEIGHT)
           , m_keys_pressed()
           , m_running(true)
           , m_screen(0)
           , m_square(0)
           , m_text_surface(0)
           , m_game_speed(STARTING_SPEED)
           , m_fallobj(m_board)
           , m_board(m_score_board)
           {}
  ~Runner() { TTF_CloseFont(m_font); SDL_FreeSurface(m_text_surface);
              SDL_FreeSurface(m_background); SDL_FreeSurface(m_square); SDL_Quit(); }

  int run();

private:
  const int WINDOW_WIDTH;
  const int WINDOW_HEIGHT;
  int initialize();
  int run_app();

  void analyze_keyboard_input(SDL_Event& event);
  void execute_keyboard_input();

  void calculate_block_position(const Coordinates& coord);
  void draw_all();
  void draw_squares_to(const std::vector<Coordinates>& coords);

  void draw_score_board();

  bool          m_keys_pressed[323];
  bool          m_running;

  SDL_Surface*  m_screen;
  SDL_Surface*  m_background;
  SDL_Surface*  m_square;
  SDL_Rect      m_game_area_rim;
  SDL_Rect      m_game_area;

  TTF_Font*     m_font;
  SDL_Color     m_text_color;
  SDL_Color     m_text_background;
  SDL_Surface*  m_text_surface;
  SDL_Rect      m_score_dest;
  SDL_Rect      m_level_dest;

  Score         m_score_board;

  float         m_game_speed;

  FallingObject m_fallobj;
  SDL_Rect      m_objpos;
  Board         m_board;
};


#endif // RUNNER_HPP_INCLUDED
