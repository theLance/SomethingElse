#include <cxxtest/TestSuite.h>

#include <boost/scoped_ptr.hpp>

#define private public

#include <HiScoreTable.hpp>

#include "CommonConstants.hpp"
#include "tst_tool/banner.hpp"

class HiScoreTableTestSuite : public CxxTest::TestSuite
{
public:
  boost::scoped_ptr<HiScoreTable> m_hiScoreTable;

  typedef std::multimap<unsigned long, std::string>::iterator HiScoreMapIterator;
  void setUp()
  {
    createTestFile(TestConsts::ENCRYPT_WITH_LAME_ALGO);
    m_hiScoreTable.reset(NULL);
  }

  void print_banner(const std::string& testcase)
  {
    banner("HiScoreTable - " + testcase);
  }

  void testComparator()
  {
    banner("Comparator - greater");
    ScoreComparator comp;
    TS_ASSERT_EQUALS(true, comp(2,1));
    banner("Comparator - smaller");
    TS_ASSERT_EQUALS(false, comp(1,2));
    banner("Comparator - equals(=less)");
    TS_ASSERT_EQUALS(false, comp(1,1));
  }

  void assertTestFileContentsInOrderFrom(TestConsts::TestContentsVectorIter vec_it,
                                         HiScoreMapIterator& it, HiScoreMapIterator end)
  {
    for(; it != end; ++it, ++vec_it)
    {
      TS_ASSERT_EQUALS(it->first, vec_it->second);
      TS_ASSERT_EQUALS(it->second, vec_it->first);
    }
  }

  void assertTestFileContentsInOrder(HiScoreMapIterator& it, HiScoreMapIterator end)
  {
    assertTestFileContentsInOrderFrom(TestConsts::ORDERED_TESTCONTENTS_VECTOR.begin(), it, end);
  }

  HiScoreMapIterator getIteratorOfRelativePosition(const HiScoreMapIterator orig,
                                                   const size_t offset)
  {
    HiScoreMapIterator it = orig;
    for(size_t i = 0; i < offset; ++i)
    {
      ++it;
    }
    return it;
  }

  void initializeTest(const std::string& banner)
  {
    print_banner(banner);
    m_hiScoreTable.reset(new HiScoreTable(TestConsts::TESTFILE));
  }

  void testLoadHiScoreTable()
  {
    initializeTest("Loading from file");
    HiScoreMapIterator it = m_hiScoreTable->m_score_table.begin();

    print_banner("Entries in order");
    HiScoreMapIterator end = getIteratorOfRelativePosition(it, HISCORE_TABLE_MAX_SIZE);
    assertTestFileContentsInOrder(it, end);

    print_banner("Only HISCORE_TABLE_MAX_SIZE entries");
    TS_ASSERT_EQUALS(m_hiScoreTable->m_score_table.size(), HISCORE_TABLE_MAX_SIZE);
    TS_ASSERT_EQUALS(m_hiScoreTable->m_score_table.end(), it);
  }

  void insertAndVerify(const std::string& name, const unsigned long score,
                       const std::size_t expectedSize)
  {
    m_hiScoreTable->add_score(name, score);
    TS_ASSERT_EQUALS(m_hiScoreTable->m_score_table.size(), expectedSize);
  }

  void scoreInsertionTester(const std::string& bannerbase,
                            const std::string& name, const unsigned long score,
                            const std::size_t insertionOffset)
  {
    tearDown();
    setUp();
    initializeTest(bannerbase);

    print_banner(bannerbase + " - size still OK");
    insertAndVerify(name, score, HISCORE_TABLE_MAX_SIZE);

    print_banner(bannerbase + " - inserted to proper place");
    HiScoreMapIterator it = getIteratorOfRelativePosition(m_hiScoreTable->m_score_table.begin(),
                                                          insertionOffset);

    TS_ASSERT_EQUALS(score, it->first);
    TS_ASSERT_EQUALS(name, it->second);

    print_banner(bannerbase + " - rest still OK");
    ++it;
    HiScoreMapIterator end =
                    getIteratorOfRelativePosition(it, HISCORE_TABLE_MAX_SIZE - 1 + insertionOffset);

    TestConsts::TestContentsVectorIter testVecBegin =
                                  TestConsts::ORDERED_TESTCONTENTS_VECTOR.begin() + insertionOffset;
    assertTestFileContentsInOrderFrom(testVecBegin, it, end);
  }

  void testAdditionsToHiScoreTable()
  {
    scoreInsertionTester("Add higher score", TestConsts::NAME1, TestConsts::SCORE1 + 1, 0);
    scoreInsertionTester("Readd highest score", "newThirdPlaceGuy", TestConsts::SCORE1, 2);
    scoreInsertionTester("New 3rd score", "newThirdPlaceGuy", TestConsts::SCORE3 + 1, 2);
  }

  void testAddScoreThatIsOffTheTable()
  {
    const std::string bannerbase("Add too low score");
    initializeTest(bannerbase);

    print_banner(bannerbase + " - size still OK");
    insertAndVerify("Loser", TestConsts::SCORE10, HISCORE_TABLE_MAX_SIZE);

    print_banner(bannerbase + " - never made it");
    HiScoreMapIterator it(m_hiScoreTable->m_score_table.begin());
    assertTestFileContentsInOrder(it, m_hiScoreTable->m_score_table.end());
  }
};
