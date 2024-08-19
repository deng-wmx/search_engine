#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "../../include/offline_phase_work/DictProdecer.h"
#include "../../include/offline_phase_work/Configuration.h"
#include "../../include/offline_phase_work/SplitTool.h"
#include "../../include/offline_phase_work/SplitToolCppJieba.h"
using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::string;

int main(int argc, char* argv[]) {

    // 读取配置文件到configuration中的map
    Configuration configuration;
    
    // 用于中文分词的工具
    SplitToolCppJieba split;


    // 构建词典和索引词典
    DictProdecer dict(&split);
    // 先创建停用词数据结构，这里用的是unorder_set
    dict.buildStop(&configuration);
    // 用停用词过滤，并创建词典
    dict.buildDict(&configuration);

    // 创建索引数据结构和文件
    dict.creatIndex();

    return 0;
}

