#include "../../include/offline_phase_work_two/tinyxml2.h"
#include "../../include/offline_phase_work_two/RSS.h"
#include <fstream>
#include <unistd.h>
#include <sstream>
#include <dirent.h>

using std::ifstream;
using std::istringstream;
using std::ofstream;

RSS::RSS(size_t capa)

{
    _rss.reserve(capa);
    _start = 0;
    _len = 0;
    _n = 0;
}

//读文件
void RSS::read(const string &filename)
{
    XMLDocument doc;
    doc.LoadFile(filename.c_str());
    if(doc.ErrorID())
    {
        std::cerr << "loadFile fail" << endl;
        return;
    }

    size_t idx = 0;

    XMLElement *itemNode = 
        doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
    while(itemNode)
    {
        string title;
        string link;
        string content;


        XMLElement *titleElement = itemNode->FirstChildElement("title");
        if (titleElement) {
            title = titleElement->GetText();
        } else {
            // 处理没有找到 title 元素的情况，直接跳过这次处理
            continue;
        }

        titleElement = itemNode->FirstChildElement("link");
        if (titleElement) {
            link = titleElement->GetText();
        } else {
            // 处理没有找到 link 元素的情况，直接跳过这次处理
            continue;
        }

        titleElement = itemNode->FirstChildElement("description");
        if (titleElement) {
            content = titleElement->GetText();
        } else {
            // 处理没有找到 title 元素的情况，直接跳过这次处理
            continue;
        }

        std::regex reg("<[^>]+>");//通用正则表达式
        content = regex_replace(content, reg, "");

        RSSIteam rssItem;

        rssItem._title = title;
        rssItem._link = link;
        rssItem._content = content;

        _rss.push_back(rssItem);
        ++idx;

        itemNode = itemNode->NextSiblingElement("item");
    }
}

//写文件
void RSS::store(const string &fileName)
{
    ofstream ofs(fileName, std::ios::app | std::ios::out); // 使用 std::ios::app 模式进行追加写入
    if(!ofs)
    {
        LogError("open file false");
        exit(-1);
    }

    // 循环一次，相当于得到了一篇文章，那么写一次偏移文件
    for(size_t idx = 0; idx != _rss.size(); ++idx)
    {
        ofs.flush();
        // 写之前得到这次写入的起始位置
        _start = getFileSize(fileName);
        ofs << "<doc>\n\t<docid>" << idx + 1
            << "</docid>\n\t<title>" << _rss[idx]._title 
            << "</title>\n\t<link>" << _rss[idx]._link 
            << "</description>\n\t<content>" << _rss[idx]._content << "</content>\n</doc>";
        ofs  << '\n' ;
        ++_n;
        ofs.flush();
        // 写之后把这个网页文件的长度计算出来
        _len = getFileSize(fileName) - _start;
        // 把位置索引写入对应的文件中
        buildOffsite();
    }

    ofs.close();

}

void RSS::buildPage(Configuration *configuration, const string &fileName) {
    // 先通过configuration获得配置文件的信息
    unordered_map<string, string> &myMap = configuration->getMap();
    string path;
    if (myMap.find(string("xml_path")) != myMap.end()) {
        path = myMap[string("xml_path")];
    }
    else {
        LogError("path false");
        exit(-1);
    }
    DIR *stream = opendir(path.c_str());
    if (!stream) {
        LogError("opendir false");
        exit(-1);
    }
    struct dirent *pdirent;
    while ((pdirent = readdir(stream)) != NULL) {
        string filePath = string(pdirent->d_name);
        if (filePath[filePath.size() - 1] != '.') {
                 // 清洗当前目录下网页
                 // 把清洗的一个文件先读到内存中
            read(path + "/" + filePath);
            store(fileName);
        }
    }
    closedir(stream);

}

// 把相应的信息写入到指定目录的文件中
void RSS::buildOffsite() {
    ofstream ofs("../../data/offsite.dat", std::ios::app | std::ios::out);
    if (!ofs) {
        LogError("open file false");
        exit(-1);
    }
    ofs << _n << " " << _start << " " << _len << "\n";
    ofs.close();
}

long RSS::getFileSize(const string& filename) {
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
