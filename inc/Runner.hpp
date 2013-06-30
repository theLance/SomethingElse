#ifndef RUNNER_HPP_INCLUDED
#define RUNNER_HPP_INCLUDED

#include "Drawer.hpp"
#include "FallingObject.hpp"


class Runner
{
public:
  Runner() : m_keys_pressed({false})
           , m_running(true)
           , m_game_speed(STARTING_SPEED)
           , m_fallobj(m_board)
           , m_board(m_score_board)
           , m_drawer()
           {}

  int run();

private:
  int initialize();
  int play();

  void analyze_keyboard_input(SDL_Event& event);
  void execute_keyboard_input();

  bool          m_keys_pressed[323];
  bool          m_running;

  float         m_game_speed;

  Score         m_score_board;

  FallingObject m_fallobj;
  Board         m_board;

  Drawer        m_drawer;
};


#endif // RUNNER_HPP_INCLUDED
