#ifndef __MYTASK_H
#define __MYTASK_H
#include "../../../include/online_phase_work/server/TcpConnection.h"
#include "../../../include/online_phase_work/server/TcpServer.h"
#include "../../../include/online_phase_work/server/ThreadPool.h"
#include "../../../include/online_phase_work/server/Preparation.h"
#include "../../../include/log4cpp/Mylogger.h"
#include "../../../include/online_phase_work/server/EditDistence.h"

class MyTask
{
    using DictType = vector<pair<string, int>>;
    using IndexType = unordered_map<string, set<int>>;
public:
    MyTask(const string &msg, const TcpConnectionPtr &con, const DictType &dict, const IndexType &index);
    // 释放掉这里editDistance对象
    ~MyTask();

    // 对客户端发过来的信息进行处理
    void process();
private:
    // 推荐
    string recommend(const string &content);

    // 召回，并填充词频和最小编辑距离
    void recallWord(const string &myChar, const string &word);
private:
    string _msg;// 这里其实就是整个小火车的内容
    string _len;
    string _flag;
    string _content;
    TcpConnectionPtr _con;
    // 方便是方便啦，但是每个任务都需要拷贝词典
    vector<pair<string, int>> _dict;// 词典
    unordered_map<string, set<int>> _index;// 索引

    // 第一个为候选词，第二个为词频，第三个为编辑距离
    vector<pair<string, pair<int, int>>> _wordFrequeAndEditDistan;

    // 计算最小编辑距离
    EditDistence *_editDistance;
};

#endif
