#ifndef LOG_H
#define LOG_H
#include <fstream>
#include <iostream>
typedef enum log_level {
  Info,
  Warning,
  Error,
  Fatal
} log_level;

void initLogger(const std::string &info_log_filename,
                const std::string &warn_log_filename,
                const std::string &error_log_filename);

class Logger
{
private:
  static Logger *m_pLoggerInstance;
  static std::ofstream m_nInfoLogFile;
  static std::ofstream m_nWarnLogFile;
  static std::ofstream m_nErrLogFile;
  static log_level m_nLevel;
  Logger()
  {
    std::cout << "Logger construct\n";
  }

public:
  static Logger *getLoggerInstance(log_level level = Info)
  {
    m_nLevel = level;
    if (m_pLoggerInstance == nullptr)
      m_pLoggerInstance = new Logger();
    return m_pLoggerInstance;
  }
  std::ostream &getStream(log_level level);
  std::ostream &log(log_level level,
                    const int line,
                    const std::string &function);
  friend void initLogger(const std::string &info_log_filename,
                         const std::string &warn_log_filename,
                         const std::string &erro_log_filename);
  ~Logger();
};

#define LOG(level) \
  Logger::getLoggerInstance(level)->log(level, __LINE__, __FUNCTION__)

#endif