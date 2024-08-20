#include "../../../include/online_phase_work/server/MyTask.h"
#include "../../../include/online_phase_work/server/EditDistence.h"
#include <sstream>

using std::istringstream;
MyTask::MyTask(const string &msg, const TcpConnectionPtr &con, const DictType &dict, const IndexType &index)
    : _msg(msg),
    _con(con),
    _dict(dict),
    _index(index),
    _editDistance(new EditDistence())
{
}
MyTask::~MyTask() {
    /* delete _editDistance; */
}
void MyTask::process()
{
    // 对小火车进行分解
    istringstream iss(_msg);
    iss >> _len >> _flag >> _content;

    if (_flag == string("0")) {
        // 执行推荐的逻辑
        string result = recommend(_content);
    }
    else if (_flag == string("1")) {
        // 执行搜索的逻辑，暂定
    }

    // 处理后的结果发送给客户端
    /* _con->sendInLoop(_msg); */
}
// 通过字符的首个字符得到该字符的整个字节数
size_t nBytescode(const unsigned char ch) {

    if((ch & 0x80) == 0) {
        return 1;  // ASCII 字符
    } else if((ch & 0xE0) == 0xC0) {
        return 2;  // 2 字节字符
    } else if((ch & 0xF0) == 0xE0) {
        return 3;  // 3 字节字符
    } else if((ch & 0xF8) == 0xF0) {
        return 4;  // 4 字节字符
    } else {
        return 0;  // 无效的 UTF-8 字符 
    }
} 
string MyTask::recommend(const string &content) {
    for (int i = 0; i < content.size(); ) {
        size_t len = nBytescode(static_cast<unsigned char>(content[i]));
        if (len == 0) {
            cout << "Invalid UTF-8 character\n";
            break;
        }   
        string myChar = content.substr(i, len);
        recallWord(myChar, content);
        i += len;
    }

    // 这里词频和最小距离数据结构已经填写好了
    for (int i = 0; i < _wordFrequeAndEditDistan.size(); ++i) {
        cout << _wordFrequeAndEditDistan[i].first << " " << _wordFrequeAndEditDistan[i].second.first <<
            " " << _wordFrequeAndEditDistan[i].second.second << "\n";
    }
    return "";
}

void MyTask::recallWord(const string &myChar, const string &word) { 
    unordered_map<string, set<int>>::iterator it;
    if (( it = _index.find(myChar)) != _index.end()) {
        // 得到索引的set
        set<int> mySet = it->second;
        for (auto & val : mySet) {
            // 得到候选词
            string candidateWords = _dict[val].first;
            int frequency = _dict[val].second;
            int editDistance = _editDistance->editDistance(word, candidateWords);
            _wordFrequeAndEditDistan.push_back({candidateWords, {frequency, editDistance}});
        }
    }
}
