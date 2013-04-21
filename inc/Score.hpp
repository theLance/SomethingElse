#ifndef SCORE_HPP_INCLUDED
#define SCORE_HPP_INCLUDED


class Score
{
public:
  Score() : m_score(0), m_level(1) {}

  void update_score(const unsigned no_of_lines);
  const unsigned get_score() const { return m_score; }
  const unsigned get_level() const { return m_level; }

private:
  unsigned m_score;
  unsigned m_level;
};


#endif // SCORE_HPP_INCLUDED
