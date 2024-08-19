#include "../../include/offline_phase_work/DictProdecer.h"
#include "../../include/offline_phase_work/Configuration.h"
#include "../../include/offline_phase_work/SplitTool.h"
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
        // 打开这些中文语料文件，进行处理
        if (filePath[filePath.size() - 1] != '.') {
            // 把文件内容读到string中
            string content = readFileToString(path + "/" + string(pdirent->d_name));
            
            // 把中文中的\r\n去掉，用前一个字母进行替换
            // 预处理，为了保证下面的for循环从1开始，防止数组越界访问
            if (content[0] == '\r' || content[0] == '\n') {
                content[0] = ' ';
            }
            for (int i = 1; i < content.size(); ++i) {
                if (content[i] == '\r' || content[i] == '\n') {
                    content[i] = content[i - 1];
                }
            }
            cout << content;
            // 中文分词
            /* vector<string> temp = _cuttor->cut(content); */
            /* for (auto & val : temp) { */
            /*     cout << val << " " << "\n"; */
            /* } */
        }
    }
    closedir(stream);
    ofs.close();
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
// 构建停用词数据结构
void DictProdecer::buildStop(Configuration *configuration) {

    // 先获取配置文件对应的map
    unordered_map<string, string> &myMap = configuration->getMap();
    // 构造中文停用词
    if (myMap.find(string("chinese_stop_words")) != myMap.end()) {
        buildCnStop(myMap[string("chinese_stop_words")]);
    }
    else {
        LogError("chinese_stop_words = nullptr");
    }

    // 构造英文停用词
    if (myMap.find(string("english_stop_words")) != myMap.end()) {
        buildEnStop(myMap[string("english_stop_words")]);
    }
    else {
        LogError("english_stop_words = nullptr");
    }
}

// 构建中文停用词数据结构（这个代码是从构建因为词典粘过来的，注释可能不对）
void DictProdecer::buildCnStop(const string &path) {
    // 读停用词文件到string中
    DIR *stream = opendir(path.c_str());
    if (!stream) {
        LogError("opendir false");
        exit(-1);
    }
    struct dirent *pdirent;
    while ((pdirent = readdir(stream)) != NULL) {
        string filePath = string(pdirent->d_name);
        if (filePath[filePath.size() - 1] != '.') {
            ifstream ifs(path + "/" + filePath);
            if (!ifs) {
                LogError("open file false");
            }
            // 停用词文件每行一个词
            string line;
            while (getline(ifs, line)) {
                _cnStop.insert(line);
            }
        }
    }
    cout << *_cnStop.begin() << "\n";
    closedir(stream);
}
  
// 构建英文文停用词数据结构（这个代码是从构建因为词典粘过来的，注释可能不对）
void DictProdecer::buildEnStop(const string &path) {
    // 读停用词文件到string中
    DIR *stream = opendir(path.c_str());
    if (!stream) {
        LogError("opendir false");
        exit(-1);
    }
    struct dirent *pdirent;
    while ((pdirent = readdir(stream)) != NULL) {
        string filePath = string(pdirent->d_name);
        if (filePath[filePath.size() - 1] != '.') {
            ifstream ifs(path + "/" + filePath);
            if (!ifs) {
                LogError("open file false");
            }
            // 停用词文件每行一个词
            string line;
            while (getline(ifs, line)) {
                _enStop.insert(line);
            }
        }
    }
    cout << *_cnStop.begin() << "\n";
    closedir(stream);
} 
