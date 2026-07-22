#ifndef ERRORLOGS_H
#define ERRORLOGS_H
#include "logger.h"

static Logger logger;

class ErrorLogs
{
public:
    static void Warning(bool isExpressionTrue,std::string message);
    static void Failed(bool isExpressionTrue,const std::string message, bool & errorflag );



private:
    ErrorLogs() {}
};

#endif // ERRORLOGS_H
