#include <cxxtest/TestSuite.h>

#include <boost/scoped_ptr.hpp>

#include <FileHandler.hpp>
#include <Encrypter.hpp>

#include "tst_tool/banner.hpp"

class EncrypterTestSuite : public CxxTest::TestSuite
{
public:
  const std::string m_testfile;
  const std::string m_testtext;
  const std::string m_testcontents;

  EncrypterTestSuite() : m_testfile("test.txt")
                       , m_testtext(std::string("TEST") + EncrypterAlgorithm::WORD_SEPARATOR + "10")
                       , m_testcontents(m_testtext + EncrypterAlgorithm::WORD_SEPARATOR +
                                        m_testtext + EncrypterAlgorithm::WORD_SEPARATOR)
                       {}

  void print_banner(const std::string& testcase)
  {
    banner("Encrypter - " + testcase);
  }

  void testLameEncrypterAlgorithm()
  {
    const std::string bannerbase("LameEncrypterAlgorithm::");
    print_banner(bannerbase + "encrypt");
    LameEncrypterAlgorithm lameAlgo;
    const std::string encrypted(lameAlgo.encrypt(m_testcontents));
    TS_ASSERT_DIFFERS(m_testcontents, encrypted);
    print_banner(bannerbase + "decrypt");
    TS_ASSERT_EQUALS(m_testcontents, lameAlgo.decrypt(encrypted));
  }

  void testEncrypterEncrypt()
  {
    print_banner("decrypt");

    FileHandler filehandler(m_testfile);
    LameEncrypterAlgorithm lameAlgo;
    filehandler.updateBuffer(lameAlgo.encrypt(m_testcontents));

    Encrypter encrypter(m_testfile);
    TS_ASSERT_EQUALS(m_testcontents, encrypter.decrypt());
  }

  void testEncrypterDecrypt()
  {
    print_banner("encrypt");

    Encrypter encrypter(m_testfile);
    encrypter.encrypt(m_testcontents);

    FileHandler filehandler(m_testfile);
    TS_ASSERT_DIFFERS(m_testcontents, filehandler.getBuffer());
  }
};
