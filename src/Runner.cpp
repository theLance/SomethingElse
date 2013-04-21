#include <Runner.hpp>

#include <sstream>


int Runner::initialize()
{
  std::cerr << "Initializing SDL" << std::endl;
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  m_screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0,
                                         SDL_HWSURFACE | SDL_DOUBLEBUF);
  if(!m_screen)
  {
    std::cerr << "Unable to load screen: " << SDL_GetError() << std::endl;
    return 1;
  }

  m_game_area.x = m_screen->w/2 - GRID_UNIT * (GRID_WIDTH/2);
  m_game_area.y = GRID_UNIT;
  m_game_area.w = GRID_UNIT * GRID_WIDTH;
  m_game_area.h = GRID_UNIT * GRID_HEIGHT;

  TTF_Init();
  m_font = TTF_OpenFont("ARIAL.TTF", 20);

  m_text_color = { 255, 255, 255 };
  m_text_background = { 0, 0, 0 };

  m_score_dest = { 10, 10, 0, 0 };
  m_level_dest = { 10, 40, 0, 0 };

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

  m_fallobj.reset_object();

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

  if(m_keys_pressed[SDLK_UP])    m_fallobj.rotate_object();
  if(m_keys_pressed[SDLK_DOWN])  m_fallobj.move_obj_down();
  if(m_keys_pressed[SDLK_LEFT])  m_fallobj.move_obj_left();
  if(m_keys_pressed[SDLK_RIGHT]) m_fallobj.move_obj_right();
}

void Runner::calculate_block_position(const Coordinates& coord)
{
  m_objpos.x = coord.x * GRID_UNIT + m_screen->w/2 - GRID_UNIT * (GRID_WIDTH/2);
  m_objpos.y = (coord.y + 1) * GRID_UNIT;
}

void Runner::draw_squares_to(const std::vector<Coordinates>& coords)
{
  for(auto coord : coords)
  {
    calculate_block_position(coord);
    SDL_BlitSurface(m_square, 0, m_screen, &m_objpos);
  }
}

void Runner::draw_score_board()
{
  std::stringstream ss;
  std::string str;

  ss << m_score_board.get_score() << " " << m_score_board.get_level();
  ss >> str;

  m_text_surface = TTF_RenderText_Shaded(m_font, str.c_str(),
                                         m_text_color, m_text_background);
  SDL_BlitSurface(m_text_surface, 0, m_screen, &m_score_dest);

  ss >> str;
  m_text_surface = TTF_RenderText_Shaded(m_font, str.c_str(),
                                         m_text_color, m_text_background);
  SDL_BlitSurface(m_text_surface, 0, m_screen, &m_level_dest);
}

void Runner::draw_all()
{
  //CLEAR + BACKGROUND + CLEAR GAME AREA
  SDL_FillRect(m_screen, 0, SDL_MapRGB(m_screen->format, 0, 0, 0));
  SDL_BlitSurface(m_background, 0, m_screen, 0);
  SDL_FillRect(m_screen, &m_game_area, SDL_MapRGB(m_screen->format, 255, 255, 255));

  //DRAW
  //Object
  draw_squares_to(m_fallobj.get_coordinates());
  //Board
  draw_squares_to(m_board.get_occupied_fields());
  //Score
  draw_score_board();

  SDL_Flip(m_screen);
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

    ///SET GAME PACE
    m_game_speed = STARTING_SPEED - m_score_board.get_level()*20;

    ///DRAW
    draw_all();
  }
  return 0;
}

int Runner::run()
{
  int ret_val = 0;
  try
  {
    ret_val = run_app();
  }
  catch(std::exception& ex)
  {
    ///declare gameover + draw score !!!
    SDL_Event event;
    SDL_Rect  sign_dest;

    m_text_surface = TTF_RenderText_Shaded(m_font, "GAME OVER", m_text_color, m_text_background);
    sign_dest.x = m_screen->w / 2 - m_text_surface->w / 2;
    sign_dest.y = m_screen->h / 2 - m_text_surface->h / 2;
    while(m_running)
    {
      if(SDL_PollEvent(&event))
      {
        analyze_keyboard_input(event);
      }
      if(m_keys_pressed[SDLK_ESCAPE]) m_running = false;

      draw_all();

      m_text_surface = TTF_RenderText_Shaded(m_font, "GAME OVER", m_text_color, m_text_background);
      SDL_BlitSurface(m_text_surface, 0, m_screen, &sign_dest);
      SDL_Flip(m_screen);
      SDL_Delay(300);
    }
  }
  catch(...)
  {
    ///unknown exception
  }
  return ret_val;
}
