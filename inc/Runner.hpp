#ifndef RUNNER_HPP_INCLUDED
#define RUNNER_HPP_INCLUDED

#include <iostream>

#include "Input.hpp"
#include "Menu.hpp"
#include "Drawer.hpp"
#include "FallingObject.hpp"
#include "HiScoreTable.hpp"


class Runner
{
public:
  Runner();

  int run();

private:
  void reset_parameters();
  int run_main_menu();
  int run_game();
  int play();
  void end_game();
  void add_new_hiscore();

  void execute_keyboard_input();

  Input         m_input;
  Menu          m_menu;
  bool          m_running;
  bool          m_paused;

  float         m_game_speed;

  Score         m_score_board;

  FallingObject m_fallobj;
  Board         m_board;

  Drawer        m_drawer;

  HiScoreTable  m_hiscore_table;
};


#endif // RUNNER_HPP_INCLUDED
