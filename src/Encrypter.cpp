#include <Encrypter.hpp>

#include <FileHandler.hpp>

#include <iomanip>
#include <sstream>

#include <boost/lexical_cast.hpp>


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

  for(std::string::const_iterator it = input.begin(); it != input.end(); ++it)
  {
    bytesep.bytes[bytecount++] = static_cast<int>(*it);
  }

  return boost::lexical_cast<std::string>(bytesep.number);
}

const std::string LameEncrypterAlgorithm::encryptDecrypt(const std::string& input,
                                                         const Operation operation) const
{
  CrypoFunct functForString = (ENCRYPT == operation) ? &LameEncrypterAlgorithm::encryptString
                                                     : &LameEncrypterAlgorithm::decryptString;
  CrypoFunct functForNumber = (ENCRYPT == operation) ? &LameEncrypterAlgorithm::encryptNumber
                                                     : &LameEncrypterAlgorithm::decryptNumber;

  std::string output("");

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

void Encrypter::encrypt(const std::string& input)
{
  m_file->updateBuffer(m_algorithm->encrypt(input));
}

const std::string Encrypter::decrypt() const
{
  return m_algorithm->decrypt(m_file->getBuffer());
}

