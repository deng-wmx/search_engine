#include <iostream>
#include <vector>
#include "../../include/offline_phase_work_two_gen_index/GenerateInvertedIndex.h"
#include "../../include/offline_phase_work_two_gen_index/SplitToolCppJieba.h"
#include "../../include/offline_phase_work_two_gen_index/Configuration.h"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;

int main(int argc, char* argv[]) {

    SplitToolCppJieba split;

    // 读取配置文件到configuration中的map
    Configuration configuration;

    GenerateInvertedIndex gen(&split);

    gen.buildOffSite();
    gen.buildStop(&configuration);
    gen.buildInvertedIndex();


    Mylogger::destroy();


    return 0;
}

