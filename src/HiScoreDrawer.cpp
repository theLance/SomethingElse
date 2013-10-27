#include <HiScoreDrawer.hpp>

#include <boost/lexical_cast.hpp>

#include <SdlBase.hpp>

#include <Defines.h>


HiScoreDrawer::HiScoreDrawer()
{
  m_title_text.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::font(), "Hi Scores",
                                              SdlExt::WHITE, SdlExt::BLACK),
                     SDL_FreeSurface);

  m_title_dest.reset(new SDL_Rect);
  m_title_dest->x = SdlExt::SdlBase::screen()->w / 2 - m_title_text->w / 2;
  m_title_dest->y = SdlExt::SdlBase::screen()->h / 15 - m_title_text->h / 2;
}

void HiScoreDrawer::draw(const HiScoreTable::HiScoreTableMap& score_map)
{
  ///CLEAR SCREEN
  SDL_FillRect(SdlExt::SdlBase::screen(), NULL,
               SDL_MapRGB(SdlExt::SdlBase::screen()->format, 0, 0, 0));

  ///DRAW TITLE
  SDL_BlitSurface(m_title_text.get(), 0, SdlExt::SdlBase::screen(), m_title_dest.get());

  ///DRAW SCORES
  SDL_Rect line_dest;
  int name_start_x_coord = SdlExt::SdlBase::screen()->w / 5;
  int score_end_x_coord = (SdlExt::SdlBase::screen()->w / 5) * 4;
  line_dest.y = m_title_dest->y + m_title_text->h * 2;

  for(HiScoreTable::HiScoreTableMap::const_iterator entry = score_map.begin();
      entry != score_map.end();
      entry++)
  {
    m_line_surface.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::font(), entry->second.c_str(),
                                               SdlExt::WHITE, SdlExt::BLACK));
    line_dest.x = name_start_x_coord;
    SDL_BlitSurface(m_line_surface.get(), 0, SdlExt::SdlBase::screen(), &line_dest);

    m_line_surface.reset(TTF_RenderText_Shaded(SdlExt::SdlBase::font(),
                                               boost::lexical_cast<std::string>(entry->first).c_str(),
                                               SdlExt::WHITE, SdlExt::BLACK));
    line_dest.x = score_end_x_coord - m_line_surface->w;
    SDL_BlitSurface(m_line_surface.get(), 0, SdlExt::SdlBase::screen(), &line_dest);

    line_dest.y += m_line_surface->h * 2;
  }

  SDL_Flip(SdlExt::SdlBase::screen());
}
