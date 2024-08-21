#ifndef __CONFIGURATION_H
#define __CONFIGURATION_H
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

class Configuration
{
public:

    // 打开配置文件读取配置文件存入map中
    Configuration();

    // 什么也不用干
    ~Configuration();

    unordered_map<string, string>& getMap();

private:
    // 用于存放读取配置文件的key和value
    unordered_map<string, string> _map;
    
};
#endif

