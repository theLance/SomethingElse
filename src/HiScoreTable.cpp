#include <HiScoreTable.hpp>

#include <Encrypter.hpp>
#include <Defines.h>

#include <boost/lexical_cast.hpp>


HiScoreTable::HiScoreTable(const std::string& filename)
{
  m_encrypted_file.reset(new Encrypter(filename));

  load_hiscore_table(m_encrypted_file->decrypt());
}

HiScoreTable::~HiScoreTable()
{
}

void HiScoreTable::load_hiscore_table(const std::string& decrypted_data)
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
      score = boost::lexical_cast<unsigned long>(
                                            decrypted_data.substr(word_begin, word_end - word_begin)
                                                );
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

void HiScoreTable::add_score(const std::string& name, const unsigned long score)
{
  m_score_table.insert(std::make_pair(score, name));
  reduceListToMaxSize();
}
