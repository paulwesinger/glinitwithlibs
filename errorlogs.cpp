#include "errorlogs.h"

void ErrorLogs::Warning(bool isExpressionTrue,std::string message) {
    if ( ! isExpressionTrue) {
        logger.logwarn(message);
    }
}

void ErrorLogs::Failed(bool isExpressionTrue,const std::string message, bool & errorflag) {
    if (! isExpressionTrue) {
        errorflag = true;
        logger.logwarn(message);
        return;
    }
    errorflag = false;
}
