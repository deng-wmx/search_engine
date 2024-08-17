#include "../../include/log4cpp/Mylogger.h"
Mylogger *Mylogger::_pInstance = nullptr;

// 构造函数
Mylogger::Mylogger() :
    myCategory(Category::getInstance("myCategory")){
        // log4cpp配置
        // 1设置日志布局
        PatternLayout *ptn = new PatternLayout();
        ptn->setConversionPattern("%d %c [%p] %m%n");

        // 2创建输出器
        OstreamAppender *pos = new OstreamAppender("console", &cout);
        pos->setLayout(ptn);

        // 3为记录器设置优先级 
        myCategory.setPriority(Priority::INFO);

        // 4为记录器附加输出器(输出到终端)
        myCategory.addAppender(pos);
}
Mylogger::~Mylogger() {
    // 释放日志有关的资源
    Category::shutdown();    
}

// 对记录器函数进行封装
void Mylogger::warn(const char *msg) {
    myCategory.warn(msg);
}
void Mylogger::error(const char *msg) {
    myCategory.error(msg);
}
void Mylogger::debug(const char *msg) {
    myCategory.debug(msg);
}
void Mylogger::info(const char *msg) {
    myCategory.info(msg);
}
void Mylogger::emerg(const char *msg) {
    myCategory.emerg(msg);
}
void Mylogger::fatal(const char *msg) {
    myCategory.fatal(msg);
}
void Mylogger::alert(const char *msg) {
    myCategory.alert(msg);
}
void Mylogger::crit(const char *msg) {
    myCategory.crit(msg);
}
void Mylogger::notice(const char *msg) {
    myCategory.notice(msg);
}

