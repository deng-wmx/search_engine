#include "../../../include/online_phase_work/server/TcpConnection.h"
#include "../../../include/online_phase_work/server/TcpServer.h"
#include "../../../include/online_phase_work/server/ThreadPool.h"
#include "../../../include/online_phase_work/server/Preparation.h"
#include "../../../include/log4cpp/Mylogger.h"
#include "../../../include/online_phase_work/server/EditDistence.h"
#include "../../../include/online_phase_work/server/MyTask.h"
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <set>

using std::cout;
using std::endl;
using std::istringstream;
using std::vector;
using std::unordered_map;
using std::pair;
using std::set;

// 即使是多个线程去读也是没有问题的
// 因为多个线程只是去读，不会修改
vector<pair<string, int>> dict;
unordered_map<string, set<int>> myIndex; 

ThreadPool *gPool = nullptr;

//连接建立
void onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!!!" << endl;
}

//消息到达
void onMessage(const TcpConnectionPtr &con )
{
    // msg是一整个火车，这里要对火车进行拆解
    string msg = con->receive();
    MyTask task(msg, con, dict, myIndex);
    gPool->addTask(std::bind(&MyTask::process, task));
}

//连接断开
void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!!" << endl;
}

void server()
{
    ThreadPool pool(4, 10);
    pool.start();
    gPool = &pool;

    TcpServer server("127.0.0.1", 8888);
    server.setAllCallback(std::move(onNewConnection)
                          , std::move(onMessage)
                          , std::move(onClose));
    server.start();
}
void ready() {
    Preparation preparation;
    preparation.bulidDict();
    dict = preparation.getDict();
    preparation.buildIndex();
    myIndex = preparation.getIndex();
}

int main(int argc, char **argv)
{
    // 预热，把词典文件和索引文件读入内存中
    ready();
    EditDistence editDistence;

    server();

    // 最后关闭log4cpp的资源
    Mylogger::destroy();
    return 0;
}

