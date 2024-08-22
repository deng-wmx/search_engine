#include <iostream>
#include <vector>
#include <set>
#include "./nlohmann/json.hpp"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::vector;
using std::set;

using json = nlohmann::json;
int main(int argc, char* argv[]) {

    std::set<std::string> mySet = {"apple", "banana", "cherry"};

    // 将set转换为JSON
    json j = mySet;

    // 将JSON对象序列化为字符串
    std::string serializedData = j.dump(); // 默认使用JSON格式的紧凑表示
    cout << serializedData << "\n";


    return 0;
}

