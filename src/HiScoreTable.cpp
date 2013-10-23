#include <HiScoreTable.hpp>

#include <Encrypter.hpp>
#include <Defines.h>

#include <boost/lexical_cast.hpp>


HiScoreTable::HiScoreTable(const std::string& filename)
{
  m_encrypted_file.reset(new Encrypter(filename));

  loadHiscoreTable(m_encrypted_file->decrypt());
}

HiScoreTable::~HiScoreTable()
{
  std::string scoreTableContents("");
  for(HiScoreTableMap::iterator it = m_score_table.begin(); it != m_score_table.end(); ++it)
  {
    scoreTableContents += it->second;
    scoreTableContents += EncrypterAlgorithm::WORD_SEPARATOR;
    scoreTableContents += boost::lexical_cast<std::string>(it->first);
    scoreTableContents += EncrypterAlgorithm::WORD_SEPARATOR;
  }
  m_encrypted_file->encrypt(scoreTableContents);
}

void HiScoreTable::loadHiscoreTable(const std::string& decrypted_data)
{
  std::size_t word_end;
  std::size_t word_begin = 0;
  unsigned counter = 0;
  std::string name;
  unsigned long score;

  while(std::string::npos !=
                   (word_end = decrypted_data.find(EncrypterAlgorithm::WORD_SEPARATOR, word_begin))
       )
  {
    if(counter & 1)
    {
      score = boost::lexical_cast<unsigned long>(decrypted_data.substr(word_begin,
                                                                       word_end - word_begin));
      add_score(name, score);
    }
    else
    {
      name = decrypted_data.substr(word_begin, word_end - word_begin);
    }

    word_end++;
    word_begin = word_end;
    counter++;
  }
}

void HiScoreTable::reduceListToMaxSize()
{
  while(HISCORE_TABLE_MAX_SIZE < m_score_table.size())
  {
    m_score_table.erase(--m_score_table.end());
  }
}

bool HiScoreTable::is_eligible(const unsigned long score)
{
  return ((m_score_table.end()--)->first < score);
}

void HiScoreTable::add_score(const std::string& name, const unsigned long score)
{
  m_score_table.insert(std::make_pair(score, name));
  reduceListToMaxSize();
}
