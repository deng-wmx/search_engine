#ifndef __REMOVEDUPLICATES_H
#define __REMOVEDUPLICATES_H
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include "../../include/log4cpp/Mylogger.h"
#include "../../include/offline_phase_work_two/SimHash.h"

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

    // 输出头部
    void coutHead(int num);

    // 依次根据_offSite到内存中，进行比较去重，并得到去重后的网页库和偏移库
    void buildPageAndOffsite();

    // 得到文件的长度
    long getFileSize(const string& filename);

    // 构建去重后的文件偏移
    void buildNewOffsite();

private:
    // Simhash对象，用于计算两个网页的指纹
    SimHash *_simHash;
    // 把位置偏移库的文件读入内存的map中
    vector<pair<int, pair<int, int>>> _offSite;

    // 新写入的去重后的偏移库
    vector<pair<int, pair<int, int>>> _newOffSite;

    int _n;// 记录去重后的网页个数
    int _start; // 记录起始位置
    int _len; // 记录长度
};

#endif
