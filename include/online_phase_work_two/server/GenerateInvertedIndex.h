#ifndef __GENERATEINVERTEDINDEX_H
#define __GENERATEINVERTEDINDEX_H
#include <vector>
#include <string>
#include "../../../include/log4cpp/Mylogger.h"
#include "./DictProdecer.h"
#include <utility>
#include <unordered_map>
#include <set>

using std::vector;
using std::pair;
using std::string;
using std::set;
using std::unordered_map;

// 自定义哈希函数
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1); // 使用位运算混合两个哈希值
    }
};

class GenerateInvertedIndex
{
public:
    GenerateInvertedIndex(SplitTool *cuttor);
    ~GenerateInvertedIndex();
    
    // 读偏移库到vector中
    void buildOffSite();

    // 读网页到string中
    string readFileToString(const string &filePath, int start, int lenth);

    // 得到停用词数据结构
    void buildStop(Configuration *config);

    // 创建倒排索引
    void buildInvertedIndex();

    void buildTF();

    void buildBF();
    

private:
    //用第一阶段的词典对象,这里为了使用，分词工具和得到停用词的数据结构
    DictProdecer *_dict;
    // 把位置偏移库的文件读入内存的vector中
    vector<pair<int, pair<int, int>>> _offSite;

    // 倒排索引数据结构，string是一个词，int表示的是文章ID，double表示这个词在这片文章中的权重
    unordered_map<string, set<pair<int, double>>> _invertedIndex;

    // 停用词数据结构
    unordered_set<string> _myStop;

    // 某个词在i号文档中的次数
    unordered_map<pair<string, int>, int, pair_hash> _TF;

    // 某个词在所有文档中的次数
    unordered_map<string, int> _DF;

};

#endif
