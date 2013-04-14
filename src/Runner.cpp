#include <Runner.hpp>

int Runner::initialize()
{
  std::cerr << "Initializing SDL" << std::endl;
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  m_screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                         SDL_HWSURFACE | SDL_DOUBLEBUF);
  if(!m_screen)
  {
    std::cerr << "Unable to load m_screen: " << SDL_GetError() << std::endl;
    return 1;
  }
  //BLACK IS TRANSPARENT
  SDL_SetColorKey(m_screen, SDL_SRCCOLORKEY, SDL_MapRGB(m_screen->format, 0, 0, 0));

  m_background = SDL_LoadBMP("background.bmp");
  if(!m_background)
  {
    std::cerr << "Unable to load bitmap: " << SDL_GetError() << std::endl;
    return 1;
  }

  m_square = SDL_LoadBMP("square.bmp");
  if(!m_square)
  {
    std::cerr << "Unable to load bitmap: " << SDL_GetError() << std::endl;
    return 1;
  }

  m_fallobj.set_bounds(m_screen, m_square);

  return 0;
}

void Runner::analyze_keyboard_input(SDL_Event& event)
{
  switch (event.type)
  {
    case SDL_QUIT:    m_running = false;                            break;
    case SDL_KEYDOWN: m_keys_pressed[event.key.keysym.sym] = true;  break;
    case SDL_KEYUP:   m_keys_pressed[event.key.keysym.sym] = false; break;
  }
}

void Runner::execute_keyboard_input()
{
  if(m_keys_pressed[SDLK_ESCAPE]) m_running = false;

  if(m_keys_pressed[SDLK_LEFT])  m_fallobj.move_obj_left();
  if(m_keys_pressed[SDLK_RIGHT]) m_fallobj.move_obj_right();
  if(m_keys_pressed[SDLK_UP])    m_fallobj.move_obj_up();
  if(m_keys_pressed[SDLK_DOWN])  m_fallobj.move_obj_down();
}

int Runner::run_app()
{
  if(initialize())
  {
    std::cerr << "\nError encountered! App shutting down." << std::endl;
    return 1;
  }

  SDL_Event event;
  float last_fall_tick = SDL_GetTicks();
  float last_input_tick = SDL_GetTicks();
  float current_time;
  m_game_speed = STARTING_SPEED;

  while(m_running)
  {
    if(SDL_PollEvent(&event))
    {
      analyze_keyboard_input(event);
    }

    ///INPUT DELAY MECHANISM
    current_time = SDL_GetTicks();
    if(current_time > last_input_tick + INPUT_SPEED)
    {
      last_input_tick = current_time;
      execute_keyboard_input();
    }

    ///FALL DELAY MECHANISM
    if(current_time > last_fall_tick + m_game_speed)
    {
      SDL_Delay(1);
      last_fall_tick = current_time;
      m_fallobj.move_obj_down();
    }

    ///CLEAR + BACKGROUND
    SDL_FillRect(m_screen, 0, SDL_MapRGB(m_screen->format, 0, 0, 0));
    SDL_BlitSurface(m_background, 0, m_screen, 0);

    ///DRAW ALL
    SDL_BlitSurface(m_square, 0, m_screen, m_fallobj.get_current_position());
    SDL_Flip(m_screen);
  }
  return 0;
}
