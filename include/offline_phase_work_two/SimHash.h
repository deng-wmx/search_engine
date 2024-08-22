#ifndef __SIMHASH_H
#define __SIMHASH_H

#define LOGGER_LEVEL LL_WARN
#include "simhash/Simhasher.hpp"

using namespace simhash;

class SimHash
{
public:
    // 构建好库里面的对象
    SimHash();

    // 释放创建的堆区对象
    ~SimHash();


    // 比较两个字符串是否相似
    bool compareStr(const string &str1, const string &str2);
    
private:
    // 计算一串字符串的指纹
    uint64_t calculateFingerprint(const string& str);

private:
    // 库里面的对象，最好只创建一次
    Simhasher *_simhasher;

};

#endif
