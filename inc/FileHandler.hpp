#ifndef FILEHANDLER_HPP_INCLUDED
#define FILEHANDLER_HPP_INCLUDED

#include <fstream>
#include <exception>


class FileReadException : public std::exception
{
public:
  FileReadException(const std::string& filename) throw() : m_filename(filename) {}
  ~FileReadException() throw() {}
  virtual const char* what() const throw();

private:
  const std::string m_filename;
};


class FileHandler
{
public:
  FileHandler(const std::string& filename) throw(FileReadException);
  virtual ~FileHandler();

  /// Returns a copy of the file's internal buffer.
  std::string getBuffer() const;

  /// Updates the file's internal buffer.
  void updateBuffer(const std::string& buffer);

private:
  void openFile();

  std::string  m_filename;
  std::fstream m_file;
};


#endif // FILEHANDLER_HPP_INCLUDED
