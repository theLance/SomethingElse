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

  /// Encrypts the contents of the HiScoreTable map to the encrypted file.
  ~HiScoreTable();

  bool is_eligible(const unsigned long score);
  void add_score(const std::string& name, const unsigned long score);
  std::vector<std::string> get_score_vector() const;

private:
  void loadHiscoreTable(const std::string& decrypted_data);
  void reduceListToMaxSize();

  typedef std::multimap<unsigned long, std::string, ScoreComparator> HiScoreTableMap;

  HiScoreTableMap              m_score_table;
  boost::scoped_ptr<Encrypter> m_encrypted_file;
};


#endif // HISCORETABLE_HPP_INCLUDED
