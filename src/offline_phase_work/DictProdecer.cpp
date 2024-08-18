#include "../../include/offline_phase_work/DictProdecer.h"
#include "../../include/offline_phase_work/Configuration.h"
#include <dirent.h>
#include <fstream>
#include <unistd.h>
#include <sstream>

using std::ifstream;
using std::istringstream;
using std::ofstream;


// 只需要传入中文分词工具(注意中文分词工具这里不是在堆区创建) 
DictProdecer::DictProdecer(SplitTool *cuttor) :
    _cuttor(cuttor) {

    }

// 释放日志系统的对象
DictProdecer::~DictProdecer() {
    Mylogger::destroy();
}
string DictProdecer::readFileToString(string fileName) {

    ifstream ifs(fileName); 

    if(!ifs){
        LogError("open file false");
        exit(-1);
    }

    //读取一个文件的所有内容先要获取文件的大小
    //将游标放到了文件的最后（尾后）
    ifs.seekg(0,std::ios::end);
    long length = ifs.tellg();//获取尾后下标，实际就是总的字符数

    char * pdata = new char[length + 1]();
    //需要将游标再放置到文件开头
    ifs.seekg(0,std::ios::beg);
    ifs.read(pdata,length);

    //content包含了文件的所有内容，包括空格、换行
    string content(pdata);
    delete [] pdata;

    ifs.close();

    return content;
}
// 创建中文词典，参数为一个中文语料目录
void DictProdecer::buildCnDict(const string &path) {
    LogInfo(path.c_str());
}

// 创建英文词典，参数为一个中文语料目录
void DictProdecer::buildEnDict(const string &path) {

    // 输出文件流写入到磁盘
    ofstream ofs;
    ofs.open("../../data/dict.dat", std::ios::app);
    if (!ofs) {
        LogError("open file false");
        exit(-1);
    }

    //LogInfo(path.c_str());
    // 用目录流依次遍历目录中的目录项
    DIR *stream = opendir(path.c_str());
    if (!stream) {
        LogError("opendir false");
        exit(-1);
    }
    struct dirent *pdirent;
    while ((pdirent = readdir(stream)) != NULL) {
        string filePath = string(pdirent->d_name);
        // 打开这些英文语料文件，进行处理
        if (filePath[filePath.size() - 1] != '.') {
            // 把文件内容读到string中
            string content = readFileToString(path + "/" + string(pdirent->d_name));
            
            // 处理这个string中的内容，清洗，大写变小写，不要的标点符号变成空格
            for (auto & val :content) {
                if (std::isalpha(val)) {
                    // 大写转成小写
                    val = std::tolower(val);
                }
                else {
                    val = ' ';
                }
            }

            // 字符串输入流用于按照空格分割字符串
            istringstream iss(content);
            string word;
            // 为了便于建立索引文件，词典是用vector存储的
            // 这里先用map进行构造，然后再拷贝到vector中
            unordered_map<string, int> tempMap;
            while (iss >> word) {
                tempMap[word]++;
            }
            

            // 因为写入的是同一个文件，所以文件流可以写到最前面，避免频繁打开关闭文件流
            /* // 输出文件流写入到磁盘 */
            /* ofstream ofs; */
            /* ofs.open("../../data/dict.dat", std::ios::app); */
            /* if (!ofs) { */
            /*     LogError("open file false"); */
            /*     exit(-1); */
            /* } */

            for (auto & val : tempMap) {
                // 写入到数据成员_dict，用于索引的构建
                _dict.push_back({val.first, val.second});
                ofs << val.first << " " << val.second << "\n";
            }

        }
    }
    closedir(stream);
    ofs.close();
}

// 创建中文词典和因为词典
void DictProdecer::buildDict(Configuration *configuration) {
    // 先获取配置文件对应的map
    unordered_map<string, string> &myMap = configuration->getMap();
    // 构造中文词典
    if (myMap.find(string("chinese_corpus_folder")) != myMap.end()) {
        buildCnDict(myMap[string("chinese_corpus_folder")]);
    }
    else {
        LogError("chinese_corpus_folder = nullptr");
    }

    // 构造英文词典
    if (myMap.find(string("english_corpus_folder")) != myMap.end()) {
        buildEnDict(myMap[string("english_corpus_folder")]);
    }
    else {
        LogError("english_corpus_folder = nullptr");
    }

}

// 创建索引文件
void DictProdecer::creatIndex() {

}

// 存储词典到到相应的目录文件
void DictProdecer::storeDict() {

}
