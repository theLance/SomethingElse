#ifndef ENCRYPTER_HPP_INCLUDED
#define ENCRYPTER_HPP_INCLUDED

#include <cstdio>

#include <boost/scoped_ptr.hpp>


class FileHandler;


class EncrypterAlgorithm
{
public:
  virtual const std::string encrypt(const std::string& input) const = 0;
  virtual const std::string decrypt(const std::string& input) const = 0;

  static const char WORD_SEPARATOR = EOF;
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
  /// En-/decrypts input, consisting of string and number pairs.
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
  ~Encrypter();

  /// Write back to file, encrypted.
  void encrypt(const std::string& input);

  /// Fetches information from the file and decrypts it into the string it returns.
  const std::string decrypt() const;

private:
  boost::scoped_ptr<FileHandler>        m_file;       ///< The file containing the encrypted data.
  boost::scoped_ptr<EncrypterAlgorithm> m_algorithm;  ///< The algorithm used for en-/decrypting.
};

#endif // ENCRYPTER_HPP_INCLUDED
