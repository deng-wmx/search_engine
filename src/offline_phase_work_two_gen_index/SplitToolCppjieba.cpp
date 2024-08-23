#include "../../include/offline_phase_work_two_gen_index/SplitToolCppJieba.h"
#include "../../include/cppjieba/Jieba.hpp"

// 这些路径需要根据你实际的安装位置调整
const char* const DICT_PATH = "../../include/cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../../include/cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../../include/cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "../../include/cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../../include/cppjieba/dict/stop_words.utf8";

cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);

// 什么都不用干
SplitToolCppJieba::SplitToolCppJieba() {

}

// 什么都不用干
SplitToolCppJieba::~SplitToolCppJieba() {

}

vector<string> SplitToolCppJieba::cut(string content) {

    std::vector<std::string> words;

    jieba.Cut(content, words, true);
    return words;

}
