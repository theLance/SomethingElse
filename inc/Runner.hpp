#ifndef RUNNER_HPP_INCLUDED
#define RUNNER_HPP_INCLUDED

#include <iostream>

#include "FallingObject.hpp"


const int WINDOW_WIDTH  = 800;
const int WINDOW_HEIGHT = 600;

#define STARTING_SPEED 600
#define INPUT_SPEED    100


class Runner
{
public:
  Runner() : m_keys_pressed(), m_running(true), m_screen(0), m_square(0)
           , m_game_speed(STARTING_SPEED) {}
  ~Runner() { SDL_FreeSurface(m_background); SDL_FreeSurface(m_square); SDL_Quit(); }

  int run_app(); ///LATER: could be called from ctor
private:
  int initialize();
  void analyze_keyboard_input(SDL_Event& event);
  void execute_keyboard_input();

  void move_block_down();

  bool          m_keys_pressed[323];
  bool          m_running;
  SDL_Surface*  m_screen;
  SDL_Surface*  m_background;
  SDL_Surface*  m_square;

  float         m_game_speed;

  FallingObject m_fallobj;
};


#endif // RUNNER_HPP_INCLUDED
