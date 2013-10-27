#ifndef DRAWER_HPP_INCLUDED
#define DRAWER_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <memory>
#include <vector>

#include "Defines.h"

class Drawer
{
public:
  Drawer() {}
  ~Drawer() {}

  int initialize();

  void draw_all(const std::vector<Coordinates>& object_coords,
                const std::vector<Coordinates>& board_coords,
                const unsigned long score,
                const unsigned level);

  void draw_gameover(const std::vector<Coordinates>& object_coords,
                     const std::vector<Coordinates>& board_coords,
                     const unsigned long score,
                     const unsigned level);

  void draw_new_hiscore_sign();

  void draw_string_input_box(const std::string& input);

private:
  void set_fixed_centered_text_and_position(std::shared_ptr<SDL_Surface>& surface,
                                            SDL_Rect& position,
                                            const std::string& text,
                                            int central_height);
  void calculate_block_position(const Coordinates& coord);
  void draw_squares_to(const std::vector<Coordinates>& coords);
  void draw_score_board(const unsigned long score, const unsigned level);

  std::shared_ptr<SDL_Surface>   m_background;
  std::shared_ptr<SDL_Surface>   m_square;
  SDL_Rect                       m_game_area_rim;
  SDL_Rect                       m_game_area;

  std::shared_ptr<SDL_Surface>   m_text_surface;
  SDL_Rect                       m_score_dest;
  SDL_Rect                       m_level_dest;
  SDL_Rect                       m_scoreboard_dest;

  SDL_Rect                       m_objpos;
};


#endif // DRAWER_HPP_INCLUDED
