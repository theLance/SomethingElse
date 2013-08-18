#ifndef TEST_CONSTS_INCLUDED
#define TEST_CONSTS_INCLUDED

#include <fstream>

#include <boost/lexical_cast.hpp>

#include <Encrypter.hpp>


const std::string createTestFileContent(const std::string& name, const unsigned long score)
{
  return (name + EncrypterAlgorithm::WORD_SEPARATOR +
          boost::lexical_cast<std::string>(score) + EncrypterAlgorithm::WORD_SEPARATOR);
}

namespace TestConsts
{

const std::string TESTFILE("test.txt");
const std::string NONEXISTANT_TESTFILE("testx.txt");

const std::string   NAME1("Mr. Number One");
const unsigned long SCORE1(200);

const std::string   NAME2("usurper guy");
const unsigned long SCORE2(SCORE1);

const std::string   NAME3("The third dude");
const unsigned long SCORE3(150);

const std::string   NAME4("How did I get it unrounded?");
const unsigned long SCORE4(129);

const std::string   NAME5_9("Filler%used//for\\padding");
const unsigned long SCORE5_9(10);

const std::string   NAME10("Didn't even begin");
const unsigned long SCORE10(0);

const std::string   NAME11("SHOULD NOT BE ON BOARD");
const unsigned long SCORE11(SCORE10);

/// padd, 3rd, 1st, padd, last, padd, after_last, 2nd, 4th, 5th, padd
const std::string  TEST_CONTENTS( createTestFileContent(NAME5_9, SCORE5_9) +
                                  createTestFileContent(NAME3, SCORE3) +
                                  createTestFileContent(NAME1, SCORE1) +
                                  createTestFileContent(NAME5_9, SCORE5_9) +
                                  createTestFileContent(NAME10, SCORE10) +
                                  createTestFileContent(NAME5_9, SCORE5_9) +
                                  createTestFileContent(NAME11, SCORE11) +
                                  createTestFileContent(NAME2, SCORE2) +
                                  createTestFileContent(NAME4, SCORE4) +
                                  createTestFileContent(NAME5_9, SCORE5_9) +
                                  createTestFileContent(NAME5_9, SCORE5_9) );

enum TestFileEncryptionFlag
{
  UNENCRYPTED = 0,
  ENCRYPT_WITH_LAME_ALGO
};

void createTestFile(const TestFileEncryptionFlag encryptionFlag)
{
  std::ofstream teststream;
  teststream.open(TESTFILE.c_str(), std::fstream::out | std::fstream::trunc);
  
  std::string contents(TEST_CONTENTS);
  if(ENCRYPT_WITH_LAME_ALGO & encryptionFlag)
  {
    LameEncrypterAlgorithm lameAlgo;
    contents = lameAlgo.encrypt(TEST_CONTENTS);
  }

  teststream << contents;
  teststream.close();
}

} // namespace TestConsts

#endif  // TEST_CONSTS_INCLUDED