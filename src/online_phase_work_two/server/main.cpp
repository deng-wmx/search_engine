#include <iostream>
#include <vector>
#include "../../../include/online_phase_work_two/server/GenerateInvertedIndex.h"
#include "../../../include/online_phase_work_two/server/SplitToolCppJieba.h"
#include "../../../include/online_phase_work_two/server/Configuration.h"
#include "../../../include/online_phase_work_two/server/Preparation.h"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;

int main(int argc, char* argv[]) {

   // SplitToolCppJieba split;

   // // 读取配置文件到configuration中的map
   // Configuration configuration;

   // GenerateInvertedIndex gen(&split);

   // gen.buildOffSite();
   // gen.buildStop(&configuration);
   // gen.buildInvertedIndex();

    Preparation preparation;
    preparation.buildInvertedIndex();
    

    Mylogger::destroy();


    return 0;
}

