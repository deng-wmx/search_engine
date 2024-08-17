#include "../../include/offline_phase_work/Configuration.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using std::string;
using std::ifstream;
using std::istringstream;
using std::cerr;
using std::unordered_map;
using std::vector;
using std::cout;

// 打开配置文件读取配置文件存入map中
Configuration::Configuration() {

    ifstream ifs("../../conf/myconf.conf");
    if (!ifs) {
        cerr << "open myconf.conf false" << "\n";
        exit(-1);
    }

    // 存储一行的内容
    string line;
    while (getline(ifs, line)) {

        // 存放切分后的单词
        string word;
        istringstream iss(line);
        vector<string> words;

        // 是否是注释的标志
        // 注意一定要设置为false
        bool flag = false;
        // 配置文件每行都输入两个单词，按照空格隔开
        while (iss >> word) {
            if (word[0] == '#') {
                break;
                flag = false;
            }
            else {
                flag = true;
                words.push_back(word);
            }
        }
        // 不是注释才存入map
        if (flag) {
            // 把读取的内容存入map中
            _map[words[0]] = words[1];
        }

    }
    ifs.close();
}

// 什么也不用干
Configuration::~Configuration() {

}

unordered_map<string, string>& Configuration::getMap() {
    return _map;
}
