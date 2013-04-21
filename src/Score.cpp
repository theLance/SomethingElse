#include <Score.hpp>

#include <Defines.h>


void Score::update_score(const unsigned no_of_lines)
{
  //base
  m_score += no_of_lines * ( BASE_SCORE_PER_LINE * m_level / 2 );
  //line bonus
  m_score += (no_of_lines - 1) * ( BASE_SCORE_PER_LINE * m_level / 2 );
  //reset level
  m_level += m_score / (100 * m_level * m_level);
}
