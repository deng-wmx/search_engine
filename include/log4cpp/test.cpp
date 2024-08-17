#include <iostream>
#include <vector>
#include "Mylogger.h"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;

int main(int argc, char* argv[]) {
    
    LogInfo("1111");
    LogError("222");
    Mylogger::destroy();

    return 0;
}

