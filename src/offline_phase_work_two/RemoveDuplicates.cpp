#include "../../include/offline_phase_work_two/RemoveDuplicates.h" 
#include <fstream>
#include <string>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::string;
using std::istringstream;

RemoveDuplicates::RemoveDuplicates() {
    _simHash = new SimHash();
    _n = 0;// 记录已经处理好的网页的个数
    _start = 0;
    _len = 0;
}

// 什么也不用干
RemoveDuplicates::~RemoveDuplicates() {
    delete _simHash;
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
    /* string temp = readFileToString("../../data/page.dat", _offSite[0].second.first, _offSite[0].second.second); */
    /* int index = temp.find("</docid>") + 8; */
    /* cout  << "<doc>\n\t<docid>" << 1 << "</docid>"; */
    /* cout << temp.substr(index) << "\n"; */

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
// 依次根据_offSite到内存中，进行比较去重，并得到去重后的网页库和偏移库
void RemoveDuplicates::buildPageAndOffsite() {

    ofstream ofs("../../data/newPage.dat", std::ios::out | std::ios::app);
    if (!ofs) {
        LogError("open file false");
        exit(-1);
    }
    // 先把第一个网页输出到文件中
    string temp = readFileToString("../../data/page.dat", _offSite[0].second.first, _offSite[0].second.second);
    // 写入前要刷新
    ofs.flush();
    _start = getFileSize("../../data/newPage.dat");
    ofs << temp;
    // 写入后也要刷新
    ofs.flush();
    _len = getFileSize("../../data/newPage.dat") - _start;
    ++_n;
    _newOffSite.push_back({_n, {_start, _len}});
    // 没当写入一次网页文件，就写入一次偏移文件
    buildNewOffsite();
    /* string temp1 = readFileToString("../../data/newPage.dat", _start, _len); */
    /* cout << temp1 << "\n"; */

    // 外层循环表示要处理的网页
    for (int i = 1; i < _offSite.size(); ++i) {
        // 需要比较看是否要写入的
        string newpage = readFileToString("../../data/page.dat", _offSite[i].second.first, _offSite[i].second.second);        

        int j = 0;
        // 内层循环表示已经去重好的网页
        for (; j < _newOffSite.size(); ++j) {
            // 去重好的，且已经写入磁盘的
            string oldpage = readFileToString("../../data/newPage.dat", _newOffSite[j].second.first, _newOffSite[j].second.second);        

            // 说明是相似的
            if (_simHash->compareStr(oldpage, newpage)) {
                // 内层循环退出,外层循环的内容不写入
                break;
            }
        }
        // 说明待去重的网页和已经处理的网页没有重复
        if (j >= _newOffSite.size()) {
            // 表示来了一个和之前都不相似的网页加入
            ++_n;
            // 把这个网页写入磁盘
            ofs.flush();
            _start = getFileSize("../../data/newPage.dat");
            // 写处理后的头
            ofs  << "<doc>\n\t<docid>" << std::to_string(_n) << "</docid>";

            // 写体
            int index = newpage.find("</docid>") + 8;
            ofs << newpage.substr(index);

            // 写完之后刷新
            ofs.flush();
            _len = getFileSize("../../data/newPage.dat") - _start;

            // 构建新的偏移库
            buildNewOffsite();
        }
    }
    // 构建文件流
    ofs.close();
}

// 得到文件的长度
long RemoveDuplicates::getFileSize(const string& filename) {
    std::ifstream file(filename, std::ios::binary);

    // 如果文件无法打开（即文件不存在）
    if (!file.is_open()) {
        // 创建一个空的文件
        std::ofstream createFile(filename, std::ios::binary);
        createFile.close();
        // 返回 0，表示文件为空
        return 0;
    }

    // 获取文件大小
    file.seekg(0, std::ios::end);  // 将文件指针移动到文件末尾
    std::streampos fileSize = file.tellg();  // 获取文件大小
    file.close();  // 关闭文件

    return static_cast<long>(fileSize);  // 返回文件大小

}

// 构建去重后的文件偏移
void RemoveDuplicates::buildNewOffsite() {
    ofstream ofs("../../data/newOffsite.dat", std::ios::app | std::ios::out);
    if (!ofs) {
        LogError("open file false");
        exit(-1);
    }
    ofs << _n << " " << _start << " " << _len << "\n";
    ofs.close();
}

