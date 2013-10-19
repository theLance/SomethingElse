#ifndef HISCORETABLE_HPP_INCLUDED
#define HISCORETABLE_HPP_INCLUDED


#include <map>
#include <vector>
#include <string>

#include <boost/scoped_ptr.hpp>

class Encrypter;


/// Comparator that ensures that score is only considered higher, if it actually is (not on equal).
struct ScoreComparator
{
  bool operator()(unsigned long a, unsigned long b)
  {
    if(a > b) return true;
    return false;
  }
};

class HiScoreTable
{
public:
  HiScoreTable(const std::string& filename);
  ~HiScoreTable();

  void add_score(const std::string& name, const unsigned long score);
  std::vector<std::string> get_score_vector() const;

private:
  void load_hiscore_table(const std::string& decrypted_data);
  void reduceListToMaxSize();

  std::multimap<unsigned long, std::string, ScoreComparator> m_score_table;
  boost::scoped_ptr<Encrypter>                               m_encrypted_file;
};


#endif // HISCORETABLE_HPP_INCLUDED
