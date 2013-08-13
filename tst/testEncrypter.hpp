#include <cxxtest/TestSuite.h>

#define private public

#include <boost/scoped_ptr.hpp>

#include <FileHandler.hpp>
#include <Encrypter.hpp>

#include "tst_tool/banner.hpp"

class EncrypterTestSuite : public CxxTest::TestSuite
{
public:
  boost::scoped_ptr<FileHandler> m_filehandler;

  const std::string m_testfile;
  const std::string m_testtext;
  const std::string m_testcontents;

  EncrypterTestSuite() : m_testfile("test.txt")
                       , m_testtext("TEST 10")    //UPDATE THIS ONCE ALGO IS DONE
                       , m_testcontents(m_testtext + '\n' + m_testtext)
                       {}

  void setUp()
  {
    m_filehandler.reset(new FileHandler(m_testfile));
    m_filehandler->updateBuffer(m_testcontents);
  }

  void print_banner(const std::string& testcase)
  {
    banner("Encrypter - " + testcase);
  }

  void testInitialization()
  {
    print_banner("std::string ctor");
    Encrypter enc_str(m_testfile);
    TS_ASSERT_DIFFERS(static_cast<FileHandler*>(NULL) ,enc_str.m_file.get());
  }
};
