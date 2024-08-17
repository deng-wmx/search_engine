#include <iostream>
#include <vector>
#include <unordered_map>
#include "../../include/offline_phase_work/Configuration.h"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;

int main(int argc, char* argv[]) {

    Configuration configuration;
    const unordered_map<string, string> &map = configuration.getMap(); 
    for (const auto & val : map) {
        cout << val.first << " " << val.second << endl;
    }

    return 0;
}

