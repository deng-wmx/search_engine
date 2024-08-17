#include <iostream>
#include <vector>
#include <unordered_map>
#include "../../include/offline_phase_work/DictProdecer.h"
#include "../../include/offline_phase_work/Configuration.h"
using std::cout;
using std::endl;
using std::cerr;
using std::cin;

int main(int argc, char* argv[]) {

    Configuration configuration;
    DictProdecer d(nullptr);
    d.buildDict(&configuration);

    return 0;
}

