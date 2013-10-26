#ifndef HISCORETABLE_HPP_INCLUDED
#define HISCORETABLE_HPP_INCLUDED


#include <map>
#include <vector>
#include <string>

#include <boost/scoped_ptr.hpp>

class Encrypter;
class HiScoreDrawer;


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

  /// Encrypts the contents of the HiScoreTable map to the encrypted file.
  ~HiScoreTable();

  bool is_eligible(const unsigned long score);
  void add_score(const std::string& name, const unsigned long score);
  void display_scores();

  typedef std::multimap<unsigned long, std::string, ScoreComparator> HiScoreTableMap;

private:
  void loadHiscoreTable(const std::string& decrypted_data);
  void reduceListToMaxSize();

  HiScoreTableMap                  m_score_table;
  boost::scoped_ptr<Encrypter>     m_encrypted_file;

  boost::scoped_ptr<HiScoreDrawer> m_drawer;
};


#endif // HISCORETABLE_HPP_INCLUDED
