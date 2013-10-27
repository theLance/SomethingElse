#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

#include <vector>
#include <string>

#include "Defines.h"

union SDL_Event;

struct Input
{
  Input() : keys_pressed(NUMBER_OF_KEYS, 0) {}

  void analyze_keyboard_input(SDL_Event& event);

  void reset();

  void wait_for_escape();

  bool add_string_input_to(std::string& iostring);

  std::vector<bool> keys_pressed;
};

#endif // INPUT_HPP_INCLUDED
