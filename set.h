#ifndef SET_H
#define SET_H

#include <deque>
#include <string>

bool saddCommand(std::deque<std::string> &args);
bool spopCommand(std::deque<std::string> &args);
bool sremCommand(std::deque<std::string> &args);
bool scardCommand(std::deque<std::string> &args);
bool smemCommand(std::deque<std::string> &args);
bool sismemCommand(std::deque<std::string> &args);
bool sinterCommand(std::deque<std::string> &args);
bool sunionCommand(std::deque<std::string> &args);
bool sdiffCommand(std::deque<std::string> &args);




#endif