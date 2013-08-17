#include <Encrypter.hpp>

#include <FileHandler.hpp>

#include <iomanip>
#include <sstream>

#include <boost/lexical_cast.hpp>


<<<<<<< HEAD
=======
const char EncrypterAlgorithm::LINE_SEPARATOR = '\n';
const char EncrypterAlgorithm::WORD_SEPARATOR = EOF;


>>>>>>> 46cca45c18bb5d360cd36def2d6e341d563d9a40
const std::string LameEncrypterAlgorithm::encryptString(const std::string& input) const
{
  std::ostringstream oss;
  for(std::string::const_iterator it = input.begin(); it != input.end(); ++it)
  {
    oss << std::setfill('0') << std::setw(m_encoded_char_width) << std::hex
        << static_cast<int>(*it);
  }
  return oss.str();
}

const std::string LameEncrypterAlgorithm::decryptString(const std::string& input) const
{
  std::string decrypted_str;
  for(std::string::const_iterator it = input.begin(); it != input.end(); it += m_encoded_char_width)
  {
    std::string str(it, it + m_encoded_char_width);
    std::istringstream iss(str);
    int intermediate;
    iss >> std::hex >> intermediate;
    decrypted_str += static_cast<char>(intermediate);
  }
  return decrypted_str;
}

const std::string LameEncrypterAlgorithm::encryptNumber(const std::string& input) const
{
  std::string encrypted_str;
  ByteSeparator bytesep;
  bytesep.number = boost::lexical_cast<unsigned long>(input);

  for(std::size_t i = 0; i < sizeof(unsigned long); ++i)
  {
    encrypted_str += bytesep.bytes[i];
  }

  return encrypted_str;
}

const std::string LameEncrypterAlgorithm::decryptNumber(const std::string& input) const
{
  ByteSeparator bytesep;
  int bytecount = 0;
<<<<<<< HEAD

=======
>>>>>>> 46cca45c18bb5d360cd36def2d6e341d563d9a40
  for(std::string::const_iterator it = input.begin(); it != input.end(); ++it)
  {
    bytesep.bytes[bytecount++] = static_cast<int>(*it);
  }
<<<<<<< HEAD

  return boost::lexical_cast<std::string>(bytesep.number);
}

const std::string LameEncrypterAlgorithm::encryptDecrypt(const std::string& input,
                                                         const Operation operation) const
=======
  return boost::lexical_cast<std::string>(bytesep.number);
}


const std::vector<std::string> LameEncrypterAlgorithm::breakIntoLines(const std::string& input)
                                                                                               const
{
  std::vector<std::string> lines;
  std::size_t newlineLocation = 0;
  std::size_t prevnewlineLocation = 0;
  while(std::string::npos != (newlineLocation = input.find(LINE_SEPARATOR, prevnewlineLocation)))
  {
    lines.push_back(input.substr(prevnewlineLocation, newlineLocation - prevnewlineLocation));
    prevnewlineLocation = newlineLocation + 1;
  }
  return lines;
}

const std::string LameEncrypterAlgorithm::encryptDecryptLine(const std::string& line,
                                                             const Operation operation) const
>>>>>>> 46cca45c18bb5d360cd36def2d6e341d563d9a40
{
  CrypoFunct functForString = (ENCRYPT == operation) ? &LameEncrypterAlgorithm::encryptString
                                                     : &LameEncrypterAlgorithm::decryptString;
  CrypoFunct functForNumber = (ENCRYPT == operation) ? &LameEncrypterAlgorithm::encryptNumber
                                                     : &LameEncrypterAlgorithm::decryptNumber;

  std::string output("");

<<<<<<< HEAD
  std::size_t word_end;
  std::size_t word_begin = 0;
  unsigned counter = 0;

  while(std::string::npos != (word_end = input.find(WORD_SEPARATOR, word_begin)))
  {
    if(counter & 1)
    {
      output += (this->*functForNumber)(input.substr(word_begin, word_end - word_begin));
    }
    else
    {
      output += (this->*functForString)(input.substr(word_begin, word_end - word_begin));
    }

    output += WORD_SEPARATOR;

    word_end++;
    word_begin = word_end;
=======
  std::size_t name_end = line.find(WORD_SEPARATOR);

  output += (this->*functForString)(line.substr(0, name_end));

  output += WORD_SEPARATOR;
  name_end++;

  output += (this->*functForNumber)(line.substr(name_end,
                                                line.find(LINE_SEPARATOR, name_end) - name_end));

  output += LINE_SEPARATOR;

  return output;
}

const std::string LameEncrypterAlgorithm::encryptDecrypt(const std::string& lines,
                                                         const Operation operation) const
{
  const std::vector<std::string> linesVec = breakIntoLines(lines);

  std::string output("");
  for(std::vector<std::string>::const_iterator it = linesVec.begin(); it != linesVec.end(); ++it)
  {
    output += encryptDecryptLine(*it, operation);
>>>>>>> 46cca45c18bb5d360cd36def2d6e341d563d9a40
  }

  return output;
}

const std::string LameEncrypterAlgorithm::encrypt(const std::string& input) const
{
  return encryptDecrypt(input, ENCRYPT);
}

const std::string LameEncrypterAlgorithm::decrypt(const std::string& input) const
{
  return encryptDecrypt(input, DECRYPT);
}




Encrypter::Encrypter(const std::string& filename)
{
  m_file.reset(new FileHandler(filename));
  // replace this to use another algorithm //
  m_algorithm.reset(new LameEncrypterAlgorithm);
}

<<<<<<< HEAD
=======
///...................... UNTESTED!!!!!

>>>>>>> 46cca45c18bb5d360cd36def2d6e341d563d9a40
void Encrypter::encrypt(const std::string& input)
{
  m_file->updateBuffer(m_algorithm->encrypt(input));
}

const std::string Encrypter::decrypt() const
{
  return m_algorithm->decrypt(m_file->getBuffer());
}

