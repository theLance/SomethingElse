#include <Runner.hpp>


Runner::Runner() : m_running(true)
                 , m_paused(false)
                 , m_game_speed(STARTING_SPEED)
                 , m_fallobj(m_board)
                 , m_board(m_score_board)
{
  if(m_drawer.initialize())
  {
    std::cerr << "\nError encountered during graphics initialization! Shutting down.\n"
              << std::endl;
    throw 1;
  }
}

void Runner::reset_parameters()
{
  m_running = true;
  m_paused = false;
  m_game_speed = STARTING_SPEED;

  m_board.reset();
  m_score_board.reset();
  m_input.reset();
  m_fallobj.reset_object();
}

void Runner::execute_keyboard_input()
{
  if(m_input.keys_pressed[SDLK_ESCAPE])
  {
    m_input.keys_pressed[SDLK_ESCAPE] = false;
    throw GameOver();
  }

  if(m_input.keys_pressed[SDLK_p]) { m_paused = !m_paused; }
  if(m_paused)
  {
    return;
  }

  if(m_input.keys_pressed[SDLK_UP])
  {
    m_fallobj.rotate_object();
    m_input.keys_pressed[SDLK_UP] = false;
  }
  if(m_input.keys_pressed[SDLK_DOWN])  { m_fallobj.move_obj_down(); }
  if(m_input.keys_pressed[SDLK_LEFT])  { m_fallobj.move_obj_left(); }
  if(m_input.keys_pressed[SDLK_RIGHT]) { m_fallobj.move_obj_right(); }
}

int Runner::play()
{
  reset_parameters();

  SDL_Event event;
  float last_fall_tick = SDL_GetTicks();
  float last_input_tick = SDL_GetTicks();
  float current_time;

  while(m_running)
  {
    if(SDL_PollEvent(&event))
    {
      m_input.analyze_keyboard_input(event);
    }

    ///INPUT DELAY MECHANISM
    current_time = SDL_GetTicks();
    if(current_time > last_input_tick + INPUT_SPEED)
    {
      last_input_tick = current_time;
      execute_keyboard_input();
    }

    ///FALL DELAY MECHANISM
    if(!m_paused && current_time > last_fall_tick + m_game_speed)
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
  Menu::Option selected_option = Menu::PLAY;
  while(Menu::QUIT != selected_option)
  {
    selected_option = m_menu.run();

    switch(selected_option)
    {
      case Menu::PLAY:
      {
        int ret_val = run_game();
        if(ret_val)
        {
          return ret_val;
        }
        break;
      }
      case Menu::HI_SCORE:
        ///SHOW HISCORES!!!!!!
        break;
      case Menu::QUIT:
        break;
      default:
        std::cerr << "\nUnexpected menu option received: " << static_cast<int>(selected_option)
                  << "\nShutting down...\n";
        throw 1;
    }
  }

  return 0;
}

void Runner::end_game()
{
  ///declare gameover + draw score
  SDL_Event event;
  const std::vector<Coordinates> obj_coords(m_fallobj.get_coordinates());
  const std::vector<Coordinates> board_coords(m_board.get_occupied_fields());
  while(m_running)
  {
    if(SDL_PollEvent(&event))
    {
      m_input.analyze_keyboard_input(event);
    }
    if(m_input.keys_pressed[SDLK_ESCAPE])
    {
      m_running = false;
    }

    m_drawer.draw_gameover(obj_coords, board_coords,
                           m_score_board.get_score(), m_score_board.get_level());

    SDL_Delay(300);
  }
}

int Runner::run_game()
{
  try
  {
    play();
  }
  catch(GameOver& ex)
  {
    end_game();
  }
  catch(...)
  {
    std::cerr << "\nUnexpected exception caught in Runner::run()" << std::endl;
    return 1;
  }

  return 0;
}
