#ifndef ENCRYPTER_HPP_INCLUDED
#define ENCRYPTER_HPP_INCLUDED

#include <vector>

#include <boost/scoped_ptr.hpp>


template<typename T> class vector;
class FileHandler;


class EncrypterAlgorithm
{
public:
  virtual const std::string encrypt(const std::string& input) const = 0;
  virtual const std::string decrypt(const std::string& input) const = 0;

  static const char LINE_SEPARATOR;
  static const char WORD_SEPARATOR;
};


class LameEncrypterAlgorithm : public EncrypterAlgorithm
{
  union ByteSeparator
  {
    unsigned long number;
    unsigned char bytes[sizeof(unsigned long)];
  };

  enum Operation
  {
    ENCRYPT = 0,
    DECRYPT
  };

public:
  LameEncrypterAlgorithm() : m_encoded_char_width(2) {}

  virtual const std::string encrypt(const std::string& input) const;
  virtual const std::string decrypt(const std::string& input) const;

private:
  const std::vector<std::string> breakIntoLines(const std::string& input) const;

  /// En-/decrypts line consisting of a string, a word separator, a number and a line separator.
  const std::string encryptDecryptLine(const std::string& line, const Operation operation) const;

  /// En-/decrypts more a string consisting of more lines (calls encryptDecryptLine on them).
  const std::string encryptDecrypt(const std::string& lines, const Operation operation) const;

  /// Encrypt character stream to hex values of characters and return result as std::string.
  const std::string encryptString(const std::string& input) const;

  /// The reverse of encryptString. Duh!
  const std::string decryptString(const std::string& input) const;

  /// Encrypt number (in input string) into ASCII chars and return result as std::string.
  const std::string encryptNumber(const std::string& input) const;

  /// Take a wild guess.
  const std::string decryptNumber(const std::string& input) const;

  unsigned int m_encoded_char_width;  ///< The width of padding for encrypting strings.

  typedef const std::string(LameEncrypterAlgorithm::*CrypoFunct)(const std::string&) const;
};


class Encrypter
{
public:
  Encrypter(const std::string& filename);

  /// Write back to file, encrypted.
  void encrypt(const std::string& input);

  /// Fetches information from the file and decrypts it into the string it returns.
  const std::string decrypt() const;

private:
  /// The file containing the encrypted data.
  boost::scoped_ptr<FileHandler>        m_file;

  /// The algorithm used for en-/decrypting.
  boost::scoped_ptr<EncrypterAlgorithm> m_algorithm;
};

#endif // ENCRYPTER_HPP_INCLUDED
