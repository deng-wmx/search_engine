#include "../../include/offline_phase_work_two/SimHash.h"    

// 构建好库里面的对象
SimHash::SimHash() : _simhasher(
                                new Simhasher("../../include/offline_phase_work_two/simhash/cppjieba/dict/jieba.dict.utf8", 
                                              "../../include/offline_phase_work_two/simhash/cppjieba/dict/hmm_model.utf8", 
                                              "../../include/offline_phase_work_two/simhash/cppjieba/dict/idf.utf8", 
                                              "../../include/offline_phase_work_two/simhash/cppjieba/dict/stop_words.utf8")
                               ) {
}

// 释放创建的堆区对象
SimHash::~SimHash() {
    delete _simhasher;
}

// 计算一串字符串的指纹
uint64_t SimHash::calculateFingerprint(const string& str) {
    uint64_t temp = 0;

    // 这里5的含义就是去string的5个关键词
    // 一般来说这里取5是合适的
    _simhasher->make(str, 5, temp);
    return temp;
}

// 比较两个字符串是否相似
bool SimHash::compareStr(const string &str1, const string &str2) {
    uint64_t u1 = calculateFingerprint(str1);
    uint64_t u2 = calculateFingerprint(str2);

    return Simhasher::isEqual(u1, u2);
}
