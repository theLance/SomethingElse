#include <Input.hpp>

#include <SDL/SDL.h>


void Input::reset()
{
  keys_pressed.assign(NUMBER_OF_KEYS, 0);
}

void Input::analyze_keyboard_input(SDL_Event& event)
{
  switch (event.type)
  {
    case SDL_QUIT:    throw AbruptExit();                         break;
    case SDL_KEYDOWN: keys_pressed[event.key.keysym.sym] = true;  break;
    case SDL_KEYUP:   keys_pressed[event.key.keysym.sym] = false; break;
  }
}

void Input::wait_for_escape()
{
  bool running(true);
  SDL_Event event;
  while(running)
  {
    if(SDL_PollEvent(&event))
    {
      analyze_keyboard_input(event);
    }
    if(keys_pressed[SDLK_ESCAPE])
    {
      keys_pressed[SDLK_ESCAPE] = false;
      running = false;
    }
    SDL_Delay(100);
  }
}

bool Input::add_string_input_to(std::string& iostring)
{
  SDL_Event event;
  SDL_PollEvent(&event);
  if(SDL_KEYDOWN == event.type)
  {
    if(SDLK_RETURN == event.key.keysym.sym)
    {
      return true;
    }

    if(SDLK_BACKSPACE == event.key.keysym.sym && !iostring.empty())
    {
      iostring.pop_back();
    }
    else if(HISCORE_NAME_MAX_SIZE >= iostring.size() &&
            SDLK_BACKSLASH != event.key.keysym.unicode &&
            SDLK_SPACE <= event.key.keysym.unicode &&
            SDLK_z >= event.key.keysym.unicode)
    {
      iostring += event.key.keysym.unicode;
    }
  }
  return false;
}
