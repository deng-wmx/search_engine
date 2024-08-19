#ifndef __DICTPRODUCER_H
#define __DICTPRODUCER_H
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <set>
#include <unordered_set>
#include "../../include/log4cpp/Mylogger.h"

using std::vector;
using std::unordered_map;
using std::string;
using std::pair;
using std::set;
using std::unordered_set;

// 用于读配置文件的类
class Configuration;
// 用于中文分词的类
class SplitTool;

class DictProdecer
{
public:
    // 只需要传入中文分词工具(注意中文分词工具这里不是在堆区创建) 
    DictProdecer(SplitTool *cuttor);

    // 中文分词工具，不是在堆区创建的，那么构造函数什么也不用干
    // 但是这里用到了日志系统，所以需要释放日志对象
    ~DictProdecer();

    // 创建中文词典和因为词典
    void buildDict(Configuration *configuration);

    // 创建中文词典，参数为一个中文语料目录
    void buildCnDict(const string &path);
    
    // 创建英文词典，参数为一个中文语料目录
    void buildEnDict(const string &path);

    // 创建索引文件
    void creatIndex();

    // 存储词典到到相应的目录文件
    void storeDict();

    // 构建停用词数据结构
    void buildStop(Configuration *configuration);

    // 构建中文停用词数据结构
    void buildCnStop(const string &path);
    
    // 构建英文文停用词数据结构
    void buildEnStop(const string &path);
private:
    string readFileToString(string fileName);

private:
    // 这个先不要，可以通过Configuration类的数据成员来获得
    // 存放语录的文件路径
    // vector<string> _filesPath;

    // 存放词典（包括中文和英文），这个主要用于构建字符索引文件
    vector<pair<string, int>> _dict;

    // 存放字符的索引(这里的string不是字符串的含义，表示一个英文或者一个中文字符)
    unordered_map <string, set<int>> _index;

    // 英文停用词
    unordered_set<string> _enStop;
    
    // 中文停用词
    unordered_set<string> _cnStop;

    // 用于中文分词的对象，因为加载一次太慢，所以该对象自始自终就创建一个
    SplitTool *_cuttor;

};

#endif
