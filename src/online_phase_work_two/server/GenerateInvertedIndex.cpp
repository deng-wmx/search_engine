#include "../../../include/online_phase_work_two/server/GenerateInvertedIndex.h"
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <math.h>
#include <unistd.h>

using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::unordered_multimap;

GenerateInvertedIndex::GenerateInvertedIndex(SplitTool *cuttor) : _dict(new DictProdecer(cuttor))
{

}
GenerateInvertedIndex::~GenerateInvertedIndex() {
    delete  _dict;
}

// 读偏移库到vector中
void GenerateInvertedIndex::buildOffSite() {
    ifstream ifs("../../data/newOffsite.dat");
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

    /* for (auto & val : _offSite) { */
    /*     string temp = readFileToString("../../data/newPage.dat", val.second.first, val.second.second); */
    /*     cout << temp << "\n"; */
    /* } */
}

// 读网页到string中                                                                         
string GenerateInvertedIndex::readFileToString(const string &filePath, int start, int lenth) {

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

void GenerateInvertedIndex::buildStop(Configuration *config) {
    _dict->buildStop(config);
    _myStop = _dict->getStop();

    // 测试停用词是否构建成功
    /* cout << _myStop.size(); */
}
// 创建倒排索引
void GenerateInvertedIndex::buildInvertedIndex() {

    buildTF();
    buildBF();

    // 遍历DF构造倒排索引
    for (auto & val : _DF) {
        // 遍历TF
        for (auto & v : _TF) {
            if (val.first == v.first.first) {
                double IDF = log2(_offSite.size() * 1.0 / (val.second + 1));
                // 这里判断是因为有脏数据
                if (IDF >= 0) {
                    _invertedIndex[val.first].insert({v.first.second, v.second * IDF});
                }
            }
        }
    }

    ofstream ofs("../../data/invertIndex.dat");
    if (!ofs) {
        LogError("open file false");
        exit(-1);
    }

    for (auto & val : _invertedIndex) {
        ofs << val.first << " ";
        for (auto & v : val.second) {
            ofs << v.first << " " << v.second << " ";
        }
        ofs << "\n";
    }
}

void GenerateInvertedIndex::buildTF() {
    // 遍历网页构建TF和BF   
    for (int j = 0; j < _offSite.size(); ++j) {
        string page = readFileToString("../../data/newPage.dat", _offSite[j].second.first, _offSite[j].second.second);
        /* cout << page << "\n"; */ 

        bool flag = true;
        vector<string> words = _dict->myCut(page);
        for (int i = 0; i < words.size(); ++i) {
            // 过滤 停用词中没有这个词才去处理
            if (_myStop.find(words[i]) == _myStop.end() && words[i][0] != ' ') {

                // 统计该单词在j+1篇文章中的词频
                _TF[{words[i], j + 1}]++;

            }
        }
    }
}   
void GenerateInvertedIndex::buildBF() {
    unordered_multimap<string, int> temp;    
    for (auto & val : _TF) {
        temp.insert({val.first.first, val.first.second});
    }
    for (auto & val : temp) {
        _DF[val.first] = temp.count(val.first);
    }
}
