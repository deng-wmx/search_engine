#ifndef __MYLOGGER_H
#define __MYLOGGER_H
#include <iostream>
#include <sstream>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/RollingFileAppender.hh"
#define LogInfo(msg) \
    do { \
        std::stringstream logMessage; \
        logMessage << "[" << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "] " << msg; \
        Mylogger::getInstance()->info(logMessage.str().c_str()); \
    } while(0)

#define LogError(msg) \
    do { \
        std::stringstream logMessage; \
        logMessage << "[" << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "] " << msg; \
        Mylogger::getInstance()->error(logMessage.str().c_str()); \
    } while(0)
#define LogWarn(msg) \
    do { \
        std::stringstream logMessage; \
        logMessage << "[" << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "] " << msg; \
        Mylogger::getInstance()->warn(logMessage.str().c_str()); \
    } while(0)
#define LogDebug(msg) \
    do { \
        std::stringstream logMessage; \
        logMessage << "[" << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "] " << msg; \
        Mylogger::getInstance()->debug(logMessage.str().c_str()); \
    } while(0)


#define LogEmerg(msg) \
    do { \
        std::stringstream logMessage; \
        logMessage << "[" << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "] " << msg; \
        Mylogger::getInstance()->emerg(logMessage.str().c_str()); \
    } while(0)

#define LogFatal(msg) \
    do { \
        std::stringstream logMessage; \
        logMessage << "[" << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "] " << msg; \
        Mylogger::getInstance()->fatal(logMessage.str().c_str()); \
    } while(0)
#define LogAlert(msg) \
    do { \
        std::stringstream logMessage; \
        logMessage << "[" << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "] " << msg; \
        Mylogger::getInstance()->alert(logMessage.str().c_str()); \
    } while(0)
#define LogCrit(msg) \
    do { \
        std::stringstream logMessage; \
        logMessage << "[" << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "] " << msg; \
        Mylogger::getInstance()->crit(logMessage.str().c_str()); \
    } while(0)
#define LogNotice(msg) \
    do { \
        std::stringstream logMessage; \
        logMessage << "[" << __FILE__ << ":" << __LINE__ << " in " << __FUNCTION__ << "] " << msg; \
        Mylogger::getInstance()->notice(logMessage.str().c_str()); \
    } while(0)

using std::cin;
using std::endl;
using std::cout;

using namespace log4cpp;
class Mylogger
{
public:

    static Mylogger *getInstance() {
        // 空了才创建
        if (nullptr == _pInstance) {
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }

    static void destroy() {
        // 不空才销毁
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void emerg(const char *msg);
    void fatal(const char *msg);
    void alert(const char *msg);
    void crit(const char *msg);
    void warn(const char *msg);
    void error(const char *msg);
    void debug(const char *msg);
    void notice(const char *msg);
    void info(const char *msg);


    // 删除赋值函数和拷贝构造
    Mylogger &operator=(const Mylogger &logger) = delete;
    Mylogger(const Mylogger &logger) = delete;
private:
    // 在构造函数中，把log4cpp的记录器封装好
    Mylogger();
    ~Mylogger();

private:
    Category &myCategory;// 引用数据类型只能在初始化列表下进行初始化
    static Mylogger *_pInstance;
};

#endif
