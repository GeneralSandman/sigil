#include "io.h"
#include "log.h"
#include "api.h"
#include <stdio.h>

inline size_t IO::m_fRead(void *, size_t)
{
}
inline size_t IO::m_fWrite(const void *, size_t)
{
}
inline int IO::m_fFlush()
{
}

IO::IO(size_t max)
    : m_nProcessedBytes(0),
      m_nMaxProcessBytes(max)
{
}

IO::~IO()
{
}

inline size_t FileIO::m_fRead(void *buf, size_t len)
{
    return fread(buf, len, 1, m_pFp);
}
inline size_t FileIO::m_fWrite(const void *buf, size_t len)
{
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
    int res = fflush(m_pFp);
    fsync(fileno(m_pFp));
    if (res == 0)
        //success
        return 1;
    else
        return 0;
}

FileIO::FileIO(size_t max, const std::string &f, const char *mode)
    : IO(max),
      m_nFileName(f),
      m_pFp(fopen(f.c_str(), mode)),
      m_nBuffered(0),
      m_nSyncNum(1000)
{
}

FileIO::~FileIO()
{
    fclose(m_pFp);
}

// static const FileIO FileIOInstance();