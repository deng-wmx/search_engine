#include "../../../include/online_phase_work_two/server/Preparation.h" 
#include "../../../include/log4cpp/Mylogger.h"
#include <sstream>
#include <fstream>

using std::istringstream;
using std::ifstream;
Preparation::Preparation() {

}                               

Preparation::~Preparation() {

}

void Preparation::buildInvertedIndex() {
    ifstream ifs("../../../data/invertIndex.dat");
    if (!ifs) {
        LogError("open files false");
    }

    int i = 0;
    // 每行都是1个键，加一串int的set
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string key;

        iss >> key;

        string word1, word2;
        while (iss >> word1 >> word2) {

            /* cout << word1 << " " << word2 << " "; */
            _invertedIndex[key].insert({std::stoi(word1), std::stod(word2)});
        }
    }

    /* for (auto & val : _invertedIndex) { */
    /*     cout << val.first << " "; */
    /*     for (auto & v : val.second) { */
    /*         cout << v.first << " " << v.second << " "; */
    /*     } */
    /*     cout << "\n"; */
    /* } */

}

unordered_map<string, set<pair<int, double>>> Preparation::getInvertedIndex() const {
    return _invertedIndex;
}
