#ifndef __SPLOTTOOLCPPJIEBA_H
#define __SPLOTTOOLCPPJIEBA_H

#include "SplitTool.h"
class SplitToolCppJieba : public SplitTool
{
public:
    // 创建jieba对象
    SplitToolCppJieba();

    // 什么都不用干
    virtual ~SplitToolCppJieba();

    vector<string> cut(string content);

private:

};

#endif
