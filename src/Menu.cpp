#include <Menu.hpp>

#include <SDL/SDL.h>

#include <Defines.h>
#include <MenuDrawer.hpp>

Menu::Menu() : m_menu_drawer(new MenuDrawer)
             , m_current_choice(PLAY)
             , m_not_chosen_yet(true)
{
}

void Menu::execute_keyboard_input()
{
  if(m_input.keys_pressed[SDLK_ESCAPE])
  {
    m_not_chosen_yet = false;
    m_current_choice = QUIT;
    return;
  }

  if(m_input.keys_pressed[SDLK_RETURN])
  {
    m_input.keys_pressed[SDLK_RETURN] = false;
    m_not_chosen_yet = false;
    return;
  }

  if(m_input.keys_pressed[SDLK_UP])
  {
    if(PLAY == m_current_choice)
    {
      m_current_choice = QUIT;
    }
    else
    {
      --m_current_choice;
    }
  }

  if(m_input.keys_pressed[SDLK_DOWN])
  {
    if(QUIT == m_current_choice)
    {
      m_current_choice = PLAY;
    }
    else
    {
      ++m_current_choice;
    }
  }
}

Menu::Option Menu::run()
{
  SDL_Event event;

  m_not_chosen_yet = true;

  float last_input_tick = SDL_GetTicks();
  float current_time;

  while(m_not_chosen_yet)
  {
    m_menu_drawer->draw(m_current_choice);

    if(SDL_PollEvent(&event))
    {
      m_input.analyze_keyboard_input(event);
    }

    ///maybe use private inheritance(with execute being virtual) to avoid duplication from Runner?
    current_time = SDL_GetTicks();
    if(current_time > last_input_tick + INPUT_SPEED)
    {
      last_input_tick = current_time;
      execute_keyboard_input();
    }

    SDL_Delay(10);
  }

  return static_cast<Option>(m_current_choice);
}
