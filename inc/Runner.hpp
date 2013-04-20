#ifndef RUNNER_HPP_INCLUDED
#define RUNNER_HPP_INCLUDED

#include <iostream>

#include "FallingObject.hpp"


class Runner
{
public:
  Runner() : WINDOW_WIDTH(WIDTH), WINDOW_HEIGHT(HEIGHT), m_keys_pressed(), m_running(true)
           , m_screen(0), m_square(0), m_game_speed(STARTING_SPEED), m_fallobj(&m_board) {}
  ~Runner() { SDL_FreeSurface(m_background); SDL_FreeSurface(m_square); SDL_Quit(); }

  int run_app(); ///LATER: could be called from ctor
private:
  const int WINDOW_WIDTH;
  const int WINDOW_HEIGHT;
  int initialize();

  void analyze_keyboard_input(SDL_Event& event);
  void execute_keyboard_input();

  void calculate_block_position(Coordinates coord);
  void draw_squares_to(std::vector<Coordinates> coords);
  void draw_square_to(Coordinates coord);

  bool          m_keys_pressed[323];
  bool          m_running;

  SDL_Surface*  m_screen;
  SDL_Surface*  m_background;
  SDL_Surface*  m_square;

  float         m_game_speed;

  FallingObject m_fallobj;
  SDL_Rect      m_objpos;
  Board         m_board;
};


#endif // RUNNER_HPP_INCLUDED
