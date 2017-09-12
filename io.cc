#include "io.h"
#include "log.h"
#include "api.h"
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
    size_t res = 0;
    //res is 1 or 0
    res = fwrite(buf, len, 1, m_pFp);
    m_nBuffered += len;

    if (m_nSyncNum &&
        m_nBuffered >= m_nSyncNum)
    {
        fflush(m_pFp);
        fsync(fileno(m_pFp));
        m_nBuffered = 0;
    }

    return res;
}
inline int FileIO::m_fFlush()
{
    LOG(Debug) << "FileIO::m_fFlush" << std::endl;
    int res = fflush(m_pFp);
    fsync(fileno(m_pFp));
    if (res == 0)
        //success
        return 1;
    else
        return 0;
}

FileIO::FileIO(size_t max, FILE *f)
    : IO(max),
      m_pFp(f),
      m_nBuffered(0),
      m_nSyncNum(1000)
{
    LOG(Debug) << "class FileIO constructor" << std::endl;
}

FileIO::~FileIO()
{
    LOG(Debug) << "class FileIO destructor" << std::endl;
}

// static const FileIO FileIOInstance();