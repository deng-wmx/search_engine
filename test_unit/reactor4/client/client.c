#include "../../../include/online_phase_work/nlohmann/json.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <error.h>
#include <iostream>
#include <string>

using std::cout;
using std::string;
typedef struct {
    int len;// 载荷的长度
    int flag; // 区分是推荐还是搜索
    char buff[1000];// 存放真正发送的内容
}train_t;

// 发送n个数据，失败返回-1 
ssize_t sendn(int sock_fd, const void *buf, size_t len, int flags) {
    size_t total = 0;
    const char *p = (const char *)buf;
    while (total < len) {
        ssize_t bytes_sent = send(sock_fd, p + total, len - total, flags);
        if (bytes_sent == -1) {
            if (errno == EINTR) {
                continue; // 如果被信号中断，继续发送
            }
            return -1; // 其他错误，返回-1
        }
        total += bytes_sent;
    }
    return total;
}
// 接受n个数据，失败返回-1
ssize_t recvn(int sock_fd, void *buf, size_t len, int flags) {
    size_t total = 0;
    char *p = (char *)buf;
    while (total < len) {
        ssize_t bytes_received = recv(sock_fd, p + total, len - total, flags);
        if (bytes_received == -1) {
            if (errno == EINTR) {
                continue; // 如果被信号中断，继续接收
            }
            return -1; // 其他错误，返回-1
        } else if (bytes_received == 0) {
            break; // 对方关闭连接
        }
        total += bytes_received;
    }
    return total;
}

// 格式输出服务段发送过来的json
void formatOutput(string messages) {
    // 解析JSON字符串
    nlohmann::json json_array = nlohmann::json::parse(messages);

    // 输出JSON数组中的元素
    for (const auto& element : json_array) {
        std::cout << element.get<std::string>() << std::endl;
    }

}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        error(1, 0, "Usage: %s IP port", argv[0]);
    }

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        error(1, errno, "socket");
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr)); // 初始化为0
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        error(1, errno, "connect");
    }

    char buff[4096] = { 0 };
    fd_set main_fd;
    FD_ZERO(&main_fd);
    FD_SET(STDIN_FILENO, &main_fd);
    FD_SET(sock_fd, &main_fd);

    int nfds = (sock_fd > STDIN_FILENO) ? sock_fd : STDIN_FILENO;

    while (1) {
        fd_set read_fd = main_fd;
        int ready = select(nfds + 1, &read_fd, NULL, NULL, NULL);
        if (ready == -1) {
            error(1, errno, "select");
        }

        if (FD_ISSET(STDIN_FILENO, &read_fd)) {
            memset(buff, 0, sizeof(buff));
            int bytes = read(STDIN_FILENO, buff, sizeof(buff));
            if (bytes == 0) {
                printf("Client exiting...\n");
                break;
            }
            // 读数据到buff中啦，这里可以把换行去掉
            int len = strlen(buff);
            if (len > 0 && buff[len - 1] == '\n') {
                buff[len - 1] = '\0';
            }
            len = strlen(buff);
            // 构造小火车发送给服务端
            train_t train;
            memset(&train, 0, sizeof(train));
            train.len = len;
            train.flag = 0;
            memcpy(train.buff, buff, len);
            if (sendn(sock_fd, &train, sizeof(int) + sizeof(int) + train.len, 0) == -1) {
                printf("sendn false\n");
                exit(-1);
            }
        }

        if (FD_ISSET(sock_fd, &read_fd)) {
            memset(buff, 0, sizeof(buff));
            int bytes = recvn(sock_fd, buff, sizeof(int), 0); // -1 to ensure null termination
            
            if (bytes == -1) {
                error(1, errno, "recv");
            } else if (bytes == 0) {
                printf("Server disconnected.\n");
                break;
            } else {
                // 先收消息的长度，再收消息的内容
                int len;
                memcpy(&len, buff, sizeof(int));

                memset(buff, 0, sizeof(buff));
                recvn(sock_fd, buff, len, 0);

                formatOutput(string(buff));
            }
        }
    }

    close(sock_fd);
    return 0;
}

