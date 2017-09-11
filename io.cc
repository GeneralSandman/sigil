#include "io.h"
#include "log.h"
#include <stdio.h>

inline size_t IO::m_fRead(void *, size_t)
{
    LOG(Debug) << "IO::m_fRead" << std::endl;
}
inline size_t IO::m_fWrite(const void *, size_t)
{
    LOG(Debug) << "IO::m_fWrite" << std::endl;
}
inline int IO::m_fFlush()
{
    LOG(Debug) << "IO::m_fFlush" << std::endl;
}

IO::IO(size_t max)
    : m_nProcessedBytes(0),
      m_nMaxProcessBytes(max)
{
    LOG(Debug) << "class IO constructor" << std::endl;
}

inline size_t IO::ioRead(void *buf, size_t len)
{
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

inline size_t IO::ioWrite(const void *buf, size_t len)
{
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

inline int IO::ioFlush()
{
    m_fFlush();
}

IO::~IO()
{
    LOG(Debug) << "class IO destructor" << std::endl;
}

inline size_t FileIO::m_fRead(void *buf, size_t len)
{
    LOG(Debug) << "FileIO::m_fRead" << std::endl;
    return fread(buf, len, 1, m_pFp);
}
inline size_t FileIO::m_fWrite(const void *buf, size_t len)
{
    LOG(Debug) << "FileIO::m_fWrite" << std::endl;
    return fwrite(buf, len, 1, m_pFp);
}
inline int FileIO::m_fFlush()
{
    LOG(Debug) << "FileIO::m_fFlush" << std::endl;
}

FileIO::FileIO(size_t max)
    : IO(max),
      m_pFp(nullptr),
      m_nBuffered(0),
      m_nSyncNum(1000)
{
    LOG(Debug) << "class FileIO constructor" << std::endl;
}

FileIO::~FileIO()
{
    LOG(Debug) << "class FileIO destructor" << std::endl;
}

static const FileIO FileIOInstance();