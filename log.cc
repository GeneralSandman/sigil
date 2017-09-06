#include "log.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Logger *Logger::m_pLoggerInstance = nullptr;
std::ofstream Logger::m_nErrLogFile;
std::ofstream Logger::m_nInfoLogFile;
std::ofstream Logger::m_nWarnLogFile;
log_level Logger::m_nLevel = Info;

void initLogger(const std::string &info_log_filename,
                const std::string &warn_log_filename,
                const std::string &error_log_filename)
{
    Logger::m_nInfoLogFile.open(info_log_filename.c_str(), std::ios::in | std::ios::app);
    Logger::m_nWarnLogFile.open(warn_log_filename.c_str(), std::ios::in | std::ios::app);
    Logger::m_nErrLogFile.open(error_log_filename.c_str(), std::ios::in | std::ios::app);
}

std::ostream &Logger::getStream(log_level level)
{

    if (Info == level)
    {
        if (m_nInfoLogFile.is_open())
        {
            return m_nInfoLogFile;
        }
        else
        {
            return std::cout;
        }
    }
    else if (Warning == level)
    {
        if (m_nWarnLogFile.is_open())
        {
            return m_nWarnLogFile;
        }
        else
        {
            return std::cerr;
        }
    }
    else
    {
        if (m_nErrLogFile.is_open())
        {
            return m_nErrLogFile;
        }
        else
        {
            return std::cerr;
        }
    }
}

std::ostream &Logger::log(log_level level,
                          const int line,
                          const std::string &function)
{

    time_t t = time(0);
    char tmpBuf[156];
    strftime(tmpBuf, 156, "%Y%m%d%H%M%S", localtime(&t)); //format date and time.

    std::string level_string = "";
    switch (level)
    {
    case Info:
        level_string = "Info";
    case Warning:
        level_string = "Warning";
    case Error:
        level_string = "Error";
    case Fatal:
        level_string = "Fatal";
    }

    return getStream(level) << "[" << tmpBuf << "]"
                            << "--"
                            << "[" << level_string << "]"
                            << "--"
                            << "function (" << function << ")"
                            << "line " << line << ":"
                            << std::flush;
}

Logger::~Logger()
{
    getStream(m_nLevel) << std::endl
                        << std::flush;

    if (Fatal == m_nLevel)
    {
        m_nInfoLogFile.close();
        m_nWarnLogFile.close();
        m_nErrLogFile.close();
    }
    std::cout << "class Logger destory\n";
}