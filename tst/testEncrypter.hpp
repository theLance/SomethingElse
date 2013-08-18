#include <cxxtest/TestSuite.h>

#include <boost/scoped_ptr.hpp>

#include <FileHandler.hpp>
#include <Encrypter.hpp>

#include "CommonConstants.hpp"
#include "tst_tool/banner.hpp"

class EncrypterTestSuite : public CxxTest::TestSuite
{
public:
  void print_banner(const std::string& testcase)
  {
    banner("Encrypter - " + testcase);
  }

  void testLameEncrypterAlgorithm()
  {
    const std::string bannerbase("LameEncrypterAlgorithm::");
    print_banner(bannerbase + "encrypt");

    LameEncrypterAlgorithm lameAlgo;
    const std::string encrypted(lameAlgo.encrypt(TestConsts::TEST_CONTENTS));
    TS_ASSERT_DIFFERS(TestConsts::TEST_CONTENTS, encrypted);

    print_banner(bannerbase + "decrypt");
    TS_ASSERT_EQUALS(TestConsts::TEST_CONTENTS, lameAlgo.decrypt(encrypted));
  }

  void testEncrypterEncrypt()
  {
    print_banner("decrypt");

    createTestFile(TestConsts::ENCRYPT_WITH_LAME_ALGO);

    Encrypter encrypter(TestConsts::TESTFILE);
    TS_ASSERT_EQUALS(TestConsts::TEST_CONTENTS, encrypter.decrypt());
  }

  void testEncrypterDecrypt()
  {
    print_banner("encrypt");

    createTestFile(TestConsts::UNENCRYPTED);

    Encrypter encrypter(TestConsts::TESTFILE);
    encrypter.encrypt(TestConsts::TEST_CONTENTS);

    FileHandler filehandler(TestConsts::TESTFILE);
    TS_ASSERT_DIFFERS(TestConsts::TEST_CONTENTS, filehandler.getBuffer());
  }
};
