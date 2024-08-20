#include "TcpConnection.h"
#include "TcpServer.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>
#include <sstream>

using std::cout;
using std::endl;
using std::istringstream;

ThreadPool *gPool = nullptr;

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con)
        : _msg(msg)
          , _con(con)
    {

    }
    void process()
    {
        // 对小火车进行分解
        istringstream iss(_msg);
        iss >> len >> flag >> content;

        if (flag == string("0")) {
            // 执行推荐的逻辑
        }
        else if (flag == string("1")) {
            // 执行搜索的逻辑，暂定
        }

        // 处理后的结果发送给客户端
        /* _con->sendInLoop(_msg); */
    }
private:
    void recommend() {

    }
private:
    string _msg;// 这里其实就是整个小火车的内容
    string len;
    string flag;
    string content;
    TcpConnectionPtr _con;
};

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
    MyTask task(msg, con);
    gPool->addTask(std::bind(&MyTask::process, task));
}

//连接断开
void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!!!" << endl;
}

void test()
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

int main(int argc, char **argv)
{
    test();
    return 0;
}

