#include <MenuDrawer.hpp>

#include <SdlBase.hpp>

#include <Defines.h>
#include <Menu.hpp>


MenuDrawer::MenuDrawer()
{
  m_title_text.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::titlefont(), TITLE.c_str(),
                                              SdlExt::WHITE, SdlExt::BLACK),
                     SDL_FreeSurface);

  m_title_dest.reset(new SDL_Rect);
  m_title_dest->x = SdlExt::SdlBase::screen()->w / 2 - m_title_text->w / 2;
  m_title_dest->y = SdlExt::SdlBase::screen()->h / 4 - m_title_text->h / 2;

  m_options_text_map[Menu::PLAY] = "Play";
  m_options_text_map[Menu::HI_SCORE] = "HiScore";
  m_options_text_map[Menu::QUIT] = "Quit";
}

void MenuDrawer::draw_option(SDL_Rect& prev_rect, unsigned option, unsigned current_choice)
{
  ///CREATE TEXT
  SDL_Color text_color = (current_choice == option) ? SdlExt::WHITE : SdlExt::GREY;
  m_option_text.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::font(),
                                            m_options_text_map[option].c_str(),
                                            text_color, SdlExt::BLACK));

  ///SET NEW POSITION
  SDL_Rect current_rect = prev_rect;
  current_rect.x = SdlExt::SdlBase::screen()->w / 2 - m_option_text->w / 2;
  current_rect.y += m_option_text->h * 2;

  ///PRINT
  SDL_BlitSurface(m_option_text.get(), 0, SdlExt::SdlBase::screen(), &current_rect);

  ///REPOSITION PREV_RECT
  prev_rect = current_rect;
}

void MenuDrawer::draw(unsigned current_choice)
{
  ///CLEAR SCREEN
  SDL_FillRect(SdlExt::SdlBase::screen(), NULL,
               SDL_MapRGB(SdlExt::SdlBase::screen()->format, 0, 0, 0));

  ///DRAW TITLE
  SDL_BlitSurface(m_title_text.get(), 0, SdlExt::SdlBase::screen(), m_title_dest.get());

  ///DRAW OPTIONS
  SDL_Rect rect;
  rect.y = SdlExt::SdlBase::screen()->h / 2;

  for(unsigned option = Menu::PLAY; option <= Menu::QUIT; option++)
  {
    draw_option(rect, option, current_choice);
  }

  SDL_Flip(SdlExt::SdlBase::screen());
}
