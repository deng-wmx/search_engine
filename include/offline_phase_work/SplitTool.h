#ifndef __SPLITOOL_H
#define __SPLITOOL_H
#include <vector>
#include <string>

using std::vector;
using std::string;

class SplitTool
{
public:
    // 什么都不用干
    SplitTool();

    // 什么都不用干
    // 有虚函数，那么析构函数要设置为虚函数
    virtual ~SplitTool();

    // 被子类继承用于封装jieba对中文进行分词
    virtual vector<string> cut(string content) = 0;

private:

};

#endif
