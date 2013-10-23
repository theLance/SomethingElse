#include <SdlBase.hpp>

#include "Defines.h"

#include <iostream>


namespace SdlExt
{

std::shared_ptr<SdlBase> SdlBase::m_instance;

SdlBase::SdlBase()
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  m_screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if(!m_screen)
  {
    std::cerr << "Unable to load screen: " << SDL_GetError() << std::endl;
    // No use running without video...
    throw 1;
  }

  //BLACK IS TRANSPARENT
  SDL_SetColorKey(m_screen, SDL_SRCCOLORKEY, SDL_MapRGB(m_screen->format, 0, 0, 0));

  TTF_Init();
  m_font.reset(TTF_OpenFont("ARIAL.TTF", 20), TTF_CloseFont);
  if(!m_font)
  {
    std::cerr << "Unable to load font: " << SDL_GetError() << std::endl;
    // No use running without text...
    throw 1;
  }

  m_titlefont.reset(TTF_OpenFont("ARIAL.TTF", 60), TTF_CloseFont);
  if(!m_titlefont)  // This would be strange, since other font is already loaded successfully...
  {
    std::cerr << "Unable to load title font: " << SDL_GetError() << std::endl;
    // No use running without title text...
    throw 1;
  }
}

SdlBase::~SdlBase()
{
  SDL_Quit();
}

SdlBase& SdlBase::getInstance()
{
  if(!m_instance)
  {
    m_instance.reset(new SdlBase);
  }
  return *m_instance;
}

SDL_Surface* SdlBase::screen()
{
  return getInstance().m_screen;
}

TTF_Font* SdlBase::font()
{
  return getInstance().m_font.get();
}

TTF_Font* SdlBase::titlefont()
{
  return getInstance().m_titlefont.get();
}

}
