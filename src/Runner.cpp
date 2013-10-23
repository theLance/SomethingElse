#include <Runner.hpp>


int Runner::initialize()
{
  int ret_val = m_drawer.initialize();
  m_fallobj.reset_object();

  return ret_val;
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

  if(m_keys_pressed[SDLK_UP])    { m_fallobj.rotate_object(); m_keys_pressed[SDLK_UP] = false; }
  if(m_keys_pressed[SDLK_DOWN])  m_fallobj.move_obj_down();
  if(m_keys_pressed[SDLK_LEFT])  m_fallobj.move_obj_left();
  if(m_keys_pressed[SDLK_RIGHT]) m_fallobj.move_obj_right();
}

int Runner::play()
{
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
    m_game_speed = STARTING_SPEED - m_score_board.get_level()*25;

    ///DRAW
    m_drawer.draw_all(m_fallobj.get_coordinates(), m_board.get_occupied_fields(),
                      m_score_board.get_score(), m_score_board.get_level());
    SDL_Delay(10);
  }

  return 0;
}

int Runner::run()
{
  int ret_val = 0;

  try
  {
    ret_val = play();
    return ret_val;
  }
  catch(GameOver& ex)
  {
    ///declare gameover + draw score
    SDL_Event event;
    const std::vector<Coordinates> obj_coords(m_fallobj.get_coordinates());
    const std::vector<Coordinates> board_coords(m_board.get_occupied_fields());
    while(m_running)
    {
      if(SDL_PollEvent(&event))
      {
        analyze_keyboard_input(event);
      }
      if(m_keys_pressed[SDLK_ESCAPE])
      {
        m_running = false;
      }

      m_drawer.draw_gameover(obj_coords, board_coords,
                             m_score_board.get_score(), m_score_board.get_level());

      SDL_Delay(300);
    }
  }
  catch(...)
  {
    std::cerr << "\nUnexpected exception caught in Runner::run()" << std::endl;
    return 1;
  }

  return ret_val;
}
