#ifndef IO_H
#define IO_H

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

class IO : boost::noncopyable
{
  protected:
    size_t m_nProcessedBytes;
    size_t m_nMaxProcessBytes;

    virtual size_t m_fRead(void *, size_t) = 0;
    virtual size_t m_fWrite(const void *, size_t);
    virtual int m_fFlush();

  public:
    IO(size_t max = 0);
    size_t ioRead(void *buf, size_t len);
    size_t ioWrite(const void *buf, size_t len);
    int ioFlush();
    virtual ~IO();
};

class FileIO : public IO
{
  protected:
    FILE *m_pFp;
    size_t m_nBuffered;
    long m_nSyncNum;

    virtual size_t m_fRead(void *, size_t);
    virtual size_t m_fWrite(const void *, size_t);
    virtual int m_fFlush();

  public:
    FileIO(size_t max = 0);

    ~FileIO();
};

#endif