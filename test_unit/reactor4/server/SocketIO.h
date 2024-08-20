#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__
#include <string>

using std::string;

class SocketIO
{
public:
    explicit SocketIO(int fd);
    ~SocketIO();
    int readn(char *buf, int len);
    string readTrain();
    int writen(const char *buf, int len);

private:
    int _fd;
};

#endif
