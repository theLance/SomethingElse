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
  std::vector<Coordinates> occupied_fields;

  /*******************/
  std::vector<Coordinates> teststuff;
  teststuff.push_back(Coordinates(4,GRID_HEIGHT-5));
  teststuff.push_back(Coordinates(3,GRID_HEIGHT-4));
  teststuff.push_back(Coordinates(4,GRID_HEIGHT-3));
  teststuff.push_back(Coordinates(3,GRID_HEIGHT-2));
  for(int i = 0; i < GRID_WIDTH-1; ++i)
    teststuff.push_back(Coordinates(i,GRID_HEIGHT-1));

  m_board.register_squares_to_board(teststuff);
  /*******************/

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

    ///DRAW
    //Object
    draw_squares_to(m_fallobj.get_coordinates());
    //Board
    draw_squares_to(m_board.get_occupied_fields());

    SDL_Flip(m_screen);
  }

  return 0;
}

