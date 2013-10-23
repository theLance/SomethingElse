#ifndef SDLBASE_HPP_INCLUDED
#define SDLBASE_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <memory>


namespace SdlExt
{
const SDL_Color WHITE = { 255, 255, 255 };
const SDL_Color BLACK = { 0, 0, 0 };

class SdlBase
{
public:
  ~SdlBase();
  static SdlBase& getInstance();
  SDL_Surface* screen();
  TTF_Font* font();

private:
  SdlBase();

  SdlBase(const SdlBase&);
  void operator=(const SdlBase&);

  static std::shared_ptr<SdlBase> m_instance;

  SDL_Surface*                    m_screen; /// Released by SDL_Quit() in dtor
  std::shared_ptr<TTF_Font>       m_font;
};

}

#endif // SDLBASE_HPP_INCLUDED
