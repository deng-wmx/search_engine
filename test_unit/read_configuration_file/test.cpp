#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::string;
using std::ifstream;
using std::istringstream;

int main(int argc, char* argv[]) {
    
    ifstream ifs("../../conf/myconf.conf");
    if (!ifs) {
        cerr << "open myconf.conf false" << endl;
        exit(-1);
    }

    string line;
    while (getline(ifs, line)) {
        string word;
        istringstream iss(line);
        while (iss >> word) {
            if (word[0] == '#') {
                break;
            }
            else {
                cout << word << "1111" << endl;
            }
        }
    }

    ifs.close();
    return 0;
}

