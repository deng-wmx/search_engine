#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include "../../include/offline_phase_work_two/Configuration.h"
#include "../../include/log4cpp/Mylogger.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;

using namespace tinyxml2;

// 构造新文件的结构体
struct RSSIteam
{
    string _title;
    string _link;
    string _content;
};

class RSS
{
public:
    // 预先留好vector的大小
    RSS(size_t capa);

    //读文件
    void read(const string &filename);

    //写文件
    void store(const string &filename);

    // 构建网页库
    void buildPage(Configuration *configuration, const string &fileName);

    // 构建网页偏移库
    void buildOffsite();

    // 得到文件的长度
    long getFileSize(const string& filename);
private:
    vector<RSSIteam> _rss;
    int _start;// 记录一个网页清洗后写入文件的起始位置
    int _len;// 记录一个网页清洗后的长度
    int _n;// 记录是第几个网页
};
