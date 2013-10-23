#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

union SDL_Event;

struct Input
{
  Input() : keys_pressed({false}) {}

  void analyze_keyboard_input(SDL_Event& event);

  bool keys_pressed[323];
};

#endif // INPUT_HPP_INCLUDED
