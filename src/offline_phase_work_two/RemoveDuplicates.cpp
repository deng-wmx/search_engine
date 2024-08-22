#include "../../include/offline_phase_work_two/RemoveDuplicates.h" 
#include <fstream>
#include <string>
#include <sstream>
using std::ifstream;
using std::string;
using std::istringstream;

// 什么也不用干
RemoveDuplicates::RemoveDuplicates() {

}

// 什么也不用干
RemoveDuplicates::~RemoveDuplicates() {

}

// 读偏移库到unorder_map中
void RemoveDuplicates::buildOffSite() {

    ifstream ifs("../../data/offsite.dat");
    if (!ifs) {
        LogError("open file false");
        exit(-1);
    }

    // 存储一行的内容，每一行都是三个值
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string myFirst, mySecond, myThird;
        iss >> myFirst >> mySecond >> myThird;
        _offSite.push_back({std::stoi(myFirst), {std::stoi(mySecond), std::stoi(myThird)}});
    }

    ifs.close();


    // 测试读文件到string中
    for (auto & val : _offSite) {
        string temp = readFileToString("../../data/page.dat", val.second.first, val.second.second);
        cout << temp << "**********" << "\n";
    }
    cout << "offsize = " <<_offSite.size() << "\n";
}

// 根据起始位置，和长度，读文件到内存
string RemoveDuplicates::readFileToString(const string &filePath, int start, int lenth) {

    // 打开文件
    std::ifstream file(filePath, std::ios::binary);

    if (!file) {
        LogError("open file false");
        exit(-1);
    }


    // 移动文件读取指针到指定位置
    file.seekg(start);

    // 创建一个缓冲区来存储读取的内容
    std::vector<char> buffer(lenth + 1);

    // 读取指定长度的内容到缓冲区
    file.read(buffer.data(), lenth);
    buffer.data()[lenth] = '\0';

    if (!file) {
        LogError("read file false");
    }
    // 关闭文件
    file.close();
    return string(buffer.data());
}

