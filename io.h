#ifndef IO_H
#define IO_H

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include "log.h"

class IO : boost::noncopyable
{
protected:
  size_t m_nProcessedBytes;
  size_t m_nMaxProcessBytes;

  //we must rewrite the m_fXXX() in drived class.
  virtual size_t m_fRead(void *, size_t) = 0;
  virtual size_t m_fWrite(const void *, size_t);
  virtual int m_fFlush();

public:
  IO(size_t max = 0);
  size_t ioRead(void *buf, size_t len)
  {
    LOG(Debug) << std::endl;

    while (len)
    {
      size_t bytes_to_read = 0;
      if (m_nMaxProcessBytes && len >= m_nMaxProcessBytes)
        bytes_to_read = m_nMaxProcessBytes;
      else
        bytes_to_read = len;

      m_fRead(buf, bytes_to_read);

      buf = (char *)buf + bytes_to_read;
      len -= bytes_to_read;
      m_nProcessedBytes += bytes_to_read;
    }
  }
  size_t ioWrite(const void *buf, size_t len)
  {
    LOG(Debug) << std::endl;

    while (len)
    {
      size_t bytes_to_write = 0;
      if (m_nMaxProcessBytes && len >= m_nMaxProcessBytes)
        bytes_to_write = m_nMaxProcessBytes;
      else
        bytes_to_write = len;

      m_fWrite(buf, bytes_to_write);
      buf = (char *)buf + bytes_to_write;
      len -= bytes_to_write;
      m_nProcessedBytes += bytes_to_write;
    }
  }
  int ioFlush()
  {
    LOG(Debug) << std::endl;

    m_fFlush();
  }
  virtual ~IO();
};

class FileIO : public IO
{
protected:
  std::string m_nFileName;
  FILE *m_pFp;
  size_t m_nBuffered;
  long m_nSyncNum;

  virtual size_t m_fRead(void *, size_t);
  virtual size_t m_fWrite(const void *, size_t);
  virtual int m_fFlush();

public:
  FileIO(size_t max, const std::string &);
  void reset2Head()
  {
    rewind(m_pFp);
  }
  ~FileIO();
};

#endif