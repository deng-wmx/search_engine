#ifndef __REMOVEDUPLICATES_H
#define __REMOVEDUPLICATES_H
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include "../../include/log4cpp/Mylogger.h"

using std::vector;
using std::pair;
using std::string;

class RemoveDuplicates
{
public:
    // 什么也不用
    RemoveDuplicates();

    // 什么也不用干
    ~RemoveDuplicates();

    // 读偏移库到unorder_map中
    void buildOffSite();

    // 根据起始位置，和长度，读文件到内存
    string readFileToString(const string &filePath, int start, int lenth);

private:
    // 把位置偏移库的文件读入内存的map中
    vector<pair<int, pair<int, int>>> _offSite;

};

#endif
