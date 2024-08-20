#include "../../../include/online_phase_work/server/SocketIO.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>

using std::cout;

SocketIO::SocketIO(int fd)
    : _fd(fd)
{

}

SocketIO::~SocketIO()
{
    close(_fd);
}

//len = 10000    1500/6     1000/1
int SocketIO::readn(char *buf, int len)
{
    int left = len;
    char *pstr = buf;
    int ret = 0;

    while(left > 0)
    {
        ret = read(_fd, pstr, left);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("read error -1");
            return -1;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            pstr += ret;
            left -= ret;
        }
    }

    return len - left;
}

string SocketIO::readTrain()
{
    string train = "";
    char buf[4096] = { 0 };

    //读取前四个字节 (火车长度)
    int lenth = 0;
    readn(buf, sizeof(int));
    memcpy(&lenth, buf, sizeof(int));
    train += std::to_string(lenth);
    train += " ";

    memset(buf, 0, sizeof(buf));
    // 读取接下来的四个字节 (flag)
    int flag = 0;
    readn(buf + sizeof(int), sizeof(int));
    memcpy(&flag, buf + sizeof(int), sizeof(int));
    train += std::to_string(flag);
    train += " ";

    memset(buf, 0, sizeof(buf));
    // 读取实际内容
    readn(buf, lenth);
    train += string(buf);

    return train;
}

int SocketIO::writen(const char *buf, int len)
{
    int left = len;
    const char *pstr = buf;
    int ret = 0;

    while(left > 0)
    {
        ret = write(_fd, pstr, left);
        if(-1 == ret && errno == EINTR)
        {
            continue;
        }
        else if(-1 == ret)
        {
            perror("writen error -1");
            return -1;
        }
        else if(0 == ret)
        {
            break;
        }
        else
        {
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}
