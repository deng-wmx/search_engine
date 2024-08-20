#ifndef __PREPARATION_H
#define __PREPARATION_H
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include <set>

using std::vector;
using std::string;
using std::pair;
using std::unordered_map;
using std::set;

class Preparation
{
public:
    // 什么也不用做
    Preparation();

    // 什么也不用做
    ~Preparation();

    // buildDict
    void bulidDict();

    // buildIndex
    void buildIndex();

    // 返回词典
    vector<pair<string, int>> getDict();
    
    // 返回索引
    unordered_map<string, set<int>> getIndex();

private:
    // 从磁盘读取文件到_dict
    vector<pair<string, int>> _dict;

    // 从内存读取索引文件
    unordered_map<string, set<int>> _index;

};

#endif
