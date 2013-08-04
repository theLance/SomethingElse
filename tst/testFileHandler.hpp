#include <cxxtest/TestSuite.h>

#include <fstream>

#include <boost/scoped_ptr.hpp>

#include <FileHandler.hpp>

#include "tst_tool/banner.hpp"

class FileHandlerTestSuite : public CxxTest::TestSuite
{
public:
  const std::string m_testfile;
  const std::string m_nonexistantTestfile;
  const std::string m_testtext;
  const std::string m_testcontents;

  FileHandlerTestSuite() : m_testfile("test.txt")
                         , m_nonexistantTestfile("testx.txt")
                         , m_testtext("TEST")
                         , m_testcontents(m_testtext + '\n' + m_testtext)
                         {}

  void setUp()
  {
    std::ofstream teststream;
    teststream.open(m_testfile.c_str(), std::fstream::out | std::fstream::trunc);
    teststream << m_testcontents;
    teststream.close();
  }

  void print_banner(const std::string& testcase)
  {
    banner("FileHandler - " + testcase);
  }

  void testCreateFileHandler()
  {
    print_banner("Instantiation");
    FileHandler fh(m_testfile);
  }

  void testCannotOpen()
  {
    print_banner("FileReadError");
    TS_ASSERT_THROWS(FileHandler fh(m_nonexistantTestfile), FileReadException);
  }

  void testGetBuffer()
  {
    print_banner("getBuffer");
    FileHandler fh(m_testfile);
    std::string fstr(fh.getBuffer());
    TS_ASSERT_EQUALS(m_testcontents, fstr);
  }

  void testUpdateBuffer()
  {
    print_banner("updateBuffer");
    boost::scoped_ptr<FileHandler> fh(new FileHandler(m_testfile));
    fh->updateBuffer(m_testtext);
    fh.reset(new FileHandler(m_testfile));
    std::string fstr(fh->getBuffer());
    TS_ASSERT_EQUALS(m_testtext, fstr);
  }
};
