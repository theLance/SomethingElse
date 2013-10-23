#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include <memory>

#include <Input.hpp>

class MenuDrawer;

class Menu
{
public:
  enum Option
  {
    PLAY = 0,
    HI_SCORE,
    QUIT
  };

  Menu();
  Option run();

private:
  void execute_keyboard_input();

  std::shared_ptr<MenuDrawer> m_menu_drawer;
  Input                       m_input;
  unsigned                    m_current_choice;
  bool                        m_not_chosen_yet;
};

#endif // MENU_HPP_INCLUDED
