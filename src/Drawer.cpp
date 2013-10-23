#include <Drawer.hpp>

#include <SdlBase.hpp>

#include <iostream>

#include <boost/lexical_cast.hpp>


int Drawer::initialize()
{
  m_game_area.x = SdlExt::SdlBase::getInstance().screen()->w/2 - GRID_UNIT * (GRID_WIDTH/2);
  m_game_area.y = GRID_UNIT;
  m_game_area.w = GRID_UNIT * GRID_WIDTH;
  m_game_area.h = GRID_UNIT * GRID_HEIGHT;

  m_game_area_rim.x = m_game_area.x - 1;
  m_game_area_rim.y = m_game_area.y - 1;
  m_game_area_rim.w = m_game_area.w + 2;
  m_game_area_rim.h = m_game_area.h + 2;

  m_score_dest = { 20, 20, 0, 0 };
  m_level_dest = { 20, 50, 0, 0 };
  m_scoreboard_dest = { 10, 10, 100, 70 };

  m_background.reset(SDL_LoadBMP(BACKGROUND_IMG));
  if(!m_background)
  {
    std::cerr << "Unable to load bitmap: " << SDL_GetError() << std::endl;
    return 1;
  }

  m_square.reset(SDL_LoadBMP(SQUARE_IMG), SDL_FreeSurface);
  if(!m_square)
  {
    std::cerr << "Unable to load bitmap: " << SDL_GetError() << std::endl;
    return 1;
  }

  m_gameover_text.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::getInstance().font(),
                                              "GAME OVER", SdlExt::WHITE, SdlExt::BLACK),
                        SDL_FreeSurface);
  m_gameover_sign_dest.x = SdlExt::SdlBase::getInstance().screen()->w / 2 - m_gameover_text->w / 2;
  m_gameover_sign_dest.y = SdlExt::SdlBase::getInstance().screen()->h / 2 - m_gameover_text->h / 2;

  return 0;
}

void Drawer::calculate_block_position(const Coordinates& coord)
{
  m_objpos.x = coord.x * GRID_UNIT + SdlExt::SdlBase::getInstance().screen()->w/2
                                                                       - GRID_UNIT * (GRID_WIDTH/2);
  m_objpos.y = (coord.y + 1) * GRID_UNIT;
}

void Drawer::draw_squares_to(const std::vector<Coordinates>& coords)
{
  for(auto coord : coords)
  {
    calculate_block_position(coord);
    if(m_objpos.y > 0)
    {
      SDL_BlitSurface(m_square.get(), 0, SdlExt::SdlBase::getInstance().screen(), &m_objpos);
    }
  }
}

void Drawer::draw_score_board(const unsigned long score, const unsigned level)
{
  std::string str;

  SDL_FillRect(SdlExt::SdlBase::getInstance().screen(), &m_scoreboard_dest,
               SDL_MapRGB(SdlExt::SdlBase::getInstance().screen()->format, 0, 0, 0));

  str = "Score: " + boost::lexical_cast<std::string>(score);

  m_text_surface.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::getInstance().font(), str.c_str(),
                                             SdlExt::WHITE, SdlExt::BLACK),
                       SDL_FreeSurface);
  if(m_text_surface->w + 20 > m_scoreboard_dest.w)
  {
    m_scoreboard_dest.w = m_text_surface->w + 20;
    draw_score_board(score, level);
  }

  SDL_BlitSurface(m_text_surface.get(), 0, SdlExt::SdlBase::getInstance().screen(), &m_score_dest);

  str = "Level:  " + boost::lexical_cast<std::string>(level);
  m_text_surface.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::getInstance().font(), str.c_str(),
                                             SdlExt::WHITE, SdlExt::BLACK),
                       SDL_FreeSurface);
  SDL_BlitSurface(m_text_surface.get(), 0, SdlExt::SdlBase::getInstance().screen(), &m_level_dest);
}

void Drawer::draw_all(const std::vector<Coordinates>& object_coords,
                      const std::vector<Coordinates>& board_coords,
                      const unsigned long score,
                      const unsigned level)
{
  //BACKGROUND + CLEAR GAME AREA
  SDL_BlitSurface(m_background.get(), 0, SdlExt::SdlBase::getInstance().screen(), 0);
  SDL_FillRect(SdlExt::SdlBase::getInstance().screen(), &m_game_area_rim,
               SDL_MapRGB(SdlExt::SdlBase::getInstance().screen()->format, 0, 0, 0));
  SDL_BlitSurface(m_background.get(), &m_game_area, SdlExt::SdlBase::getInstance().screen(),
                  &m_game_area);

  //DRAW
  //Object
  draw_squares_to(object_coords);
  //Board
  draw_squares_to(board_coords);
  //Score
  draw_score_board(score, level);

  SDL_Flip(SdlExt::SdlBase::getInstance().screen());
}

void Drawer::draw_gameover(const std::vector<Coordinates>& object_coords,
                           const std::vector<Coordinates>& board_coords,
                           const unsigned long score,
                           const unsigned level)
{
  draw_all(object_coords, board_coords, score, level);
  SDL_BlitSurface(m_gameover_text.get(), 0, SdlExt::SdlBase::getInstance().screen(),
                  &m_gameover_sign_dest);
  SDL_Flip(SdlExt::SdlBase::getInstance().screen());
}
