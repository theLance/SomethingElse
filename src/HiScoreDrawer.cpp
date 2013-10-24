#include <HiScoreDrawer.hpp>

#include <SdlBase.hpp>

#include <Defines.h>


HiScoreDrawer::HiScoreDrawer()
{
  m_title_text.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::font(), "Hi Scores",
                                              SdlExt::WHITE, SdlExt::BLACK),
                     SDL_FreeSurface);

  m_title_dest.reset(new SDL_Rect);
  m_title_dest->x = SdlExt::SdlBase::screen()->w / 2 - m_title_text->w / 2;
  m_title_dest->y = SdlExt::SdlBase::screen()->h / 12 - m_title_text->h / 2;
}

void HiScoreDrawer::display_board(const std::vector<std::string>& score_vector)
{
  ///CLEAR SCREEN
  SDL_FillRect(SdlExt::SdlBase::screen(), NULL,
               SDL_MapRGB(SdlExt::SdlBase::screen()->format, 0, 0, 0));

  ///DRAW TITLE
  SDL_BlitSurface(m_title_text.get(), 0, SdlExt::SdlBase::screen(), m_title_dest.get());

  ///DRAW SCORES
  SDL_Rect line_dest;
  line_dest.y = m_title_dest->y + m_title_text->h;
  line_dest.x = SdlExt::SdlBase::screen()->w / 5;

  for(std::vector<std::string>::const_iterator line = score_vector.begin();
      line != score_vector.end();
      line++)
  {
    m_line_surface.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::font(), line->c_str(),
                                               SdlExt::WHITE, SdlExt::BLACK));

    line_dest.y += m_line_surface->h * 2;

    SDL_BlitSurface(m_line_surface.get(), 0, SdlExt::SdlBase::screen(), &line_dest);
  }

  SDL_Flip(SdlExt::SdlBase::screen());
}

void HiScoreDrawer::draw(const std::vector<std::string>& score_vector)
{
  SDL_Event event;
  bool running(true);

  while(running)
  {
    display_board(score_vector);

    if(SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
        case SDL_KEYDOWN:
          running = false;
          break;
        default:
          break;
      }
    }

    SDL_Delay(10);
  }
}
