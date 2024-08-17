#include "../../include/offline_phase_work/DictProdecer.h"
#include "../../include/offline_phase_work/Configuration.h"


// 只需要传入中文分词工具(注意中文分词工具这里不是在堆区创建) 
DictProdecer::DictProdecer(SplitTool *cuttor) :
    _cuttor(cuttor) {

    }

// 释放日志系统的对象
DictProdecer::~DictProdecer() {
    Mylogger::destroy();
}
// 创建中文词典，参数为一个中文语料目录
void DictProdecer::buildCnDict(const string &path) {
    cout << path << "111" << "\n";
}

// 创建英文词典，参数为一个中文语料目录
void DictProdecer::buildEnDict(const string &path) {
    cout << path << "222" << "\n";
}

// 创建中文词典和因为词典
void DictProdecer::buildDict(Configuration *configuration) {
    // 先获取配置文件对应的map
    unordered_map<string, string> &myMap = configuration->getMap();
    // 构造中文词典
    if (myMap.find(string("chinese_corpus_folder")) != myMap.end()) {
        buildCnDict(myMap[string("chinese_corpus_folder")]);
    }
    else {
        LogError("chinese_corpus_folder = nullptr");
    }

    // 构造英文词典
    if (myMap.find(string("english_corpus_folder")) != myMap.end()) {
        buildCnDict(myMap[string("english_corpus_folder")]);
    }
    else {
        LogError("english_corpus_folder = nullptr");
    }

}

// 创建索引文件
void DictProdecer::creatIndex() {

}

// 存储词典到到相应的目录文件
void DictProdecer::storeDict() {

}
