#include "../../../include/online_phase_work/server/Preparation.h"
#include <fstream>
#include "../../../include/log4cpp/Mylogger.h"
#include <sstream>

using std::ifstream;
using std::istringstream;

// 什么也不用做
Preparation::Preparation() {

}

// 什么也不用做
Preparation::~Preparation() {

}

// buildDict
void Preparation::bulidDict() {
    ifstream ifs("../../../data/dict.dat");
    if (!ifs) {
        LogError("open files false");
    }
    // 每行都是两个单词，一个词一个词频
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string word;
        pair<string, int> temp;
        bool flag = true;
        while (iss >> word) {
            
            // 处理第一个单词的逻辑
            if (flag) {
                temp.first = word;
                flag = false;
            }
            else {
                temp.second = std::stoi(word);
            }
        }
        // 把这个对组插入vector中
        _dict.push_back(temp);
    }
}

// buildIndex
void Preparation::buildIndex() {
    ifstream ifs("../../../data/dictIndex.dat");
    if (!ifs) {
        LogError("open files false");
    }
    int i = 0;
    // 每行都是1个键，加一串int的set
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string word;

        // 是否是一行第一个词的标志
        bool flag = true;
        string temp;// 用于报错第一个单词
        while (iss >> word) {
           // 保存每一行的第一个词
           // 处理第一个单词的逻辑
           if (flag) {
               flag = false;
               temp = word;
               ++i;
           }// 这里肯定是第二个词,把第二个词插入对应的set中
           else {
               _index[temp].insert(std::stoi(word));
           }
        }
    }
}

// 返回词典
vector<pair<string, int>> Preparation::getDict() {
    return _dict;
}

// 返回索引
unordered_map<string, set<int>> Preparation::getIndex() {
    return _index;
}
