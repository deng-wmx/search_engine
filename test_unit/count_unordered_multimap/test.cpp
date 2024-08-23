#include <iostream>
#include <vector>
#include <unordered_map>

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::unordered_multimap;

int main(int argc, char* argv[]) {
    
    unordered_multimap<int,int> m;
    m.insert({1, 1});
    m.insert({1, 2});

    int num = m.count(1);
    cout << num << "\n";
    return 0;
}

