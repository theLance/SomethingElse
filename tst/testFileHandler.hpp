#include <cxxtest/TestSuite.h>

#include <FileHandler.hpp>

#include "CommonConstants.hpp"
#include "tst_tool/banner.hpp"

class FileHandlerTestSuite : public CxxTest::TestSuite
{
public:
  void setUp()
  {
    createTestFile(TestConsts::UNENCRYPTED);
  }

  void print_banner(const std::string& testcase)
  {
    banner("FileHandler - " + testcase);
  }

  void testCreateFileHandler()
  {
    print_banner("Instantiation");
    FileHandler fh(TestConsts::TESTFILE);
  }

  void testCannotOpen()
  {
    print_banner("FileReadError");
    TS_ASSERT_THROWS(FileHandler fh(TestConsts::NONEXISTANT_TESTFILE), FileReadException);
  }

  void testGetBuffer()
  {
    print_banner("getBuffer");
    FileHandler fh(TestConsts::TESTFILE);
    TS_ASSERT_EQUALS(TestConsts::TEST_CONTENTS, fh.getBuffer());
  }

  void testUpdateBuffer()
  {
    print_banner("updateBuffer");
    FileHandler fh(TestConsts::TESTFILE);
    const std::string random_text(TestConsts::TESTFILE + TestConsts::NONEXISTANT_TESTFILE);
    fh.updateBuffer(random_text);
    TS_ASSERT_EQUALS(random_text, fh.getBuffer());
  }
};
