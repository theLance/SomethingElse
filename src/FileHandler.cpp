#include <FileHandler.hpp>

#include <sstream>


FileHandler::FileHandler(const std::string& filename) throw(FileReadException)
                                                                              : m_filename(filename)
{
  m_file.open(m_filename.c_str(), std::fstream::in);
  if(!m_file.is_open())
  {
    throw FileReadException(filename);
  }
}

FileHandler::~FileHandler()
{
  m_file.close();
}

std::string FileHandler::getBuffer() const
{
  std::stringstream sstr;
  sstr << m_file.rdbuf();
  return sstr.str();
}

void FileHandler::updateBuffer(const std::string& buffer)
{
  m_file.close();
  m_file.open(m_filename.c_str(), std::fstream::out | std::fstream::trunc);
  m_file << buffer;
}


const char* FileReadException::what() const throw()
{
  std::string reason(m_filename);
  reason += " cannot be opened!";
  return reason.c_str();
}
