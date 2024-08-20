#ifndef __EDITDISTENCE_H
#define __EDITDISTENCE_H
#include <string>

class EditDistence
{
public:
    // 什么也不用干
    EditDistence();

    // 什么也不用干
    ~EditDistence();
    //1. 求取一个字符占据的字节数
    size_t nBytesCode(const char ch);
    //2. 求取一个字符串的字符长度
    std::size_t length(const std::string &str);
    //3. 中英文通用的最小编辑距离算法
    int editDistance(const std::string & lhs, const std::string &rhs);


private:

};

#endif
