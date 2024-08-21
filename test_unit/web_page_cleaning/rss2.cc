#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;

using namespace tinyxml2;

struct RSSIteam
{
    string _title;
    string _link;
    string _content;
};

class RSS
{
public:
    RSS(size_t capa)
    {
        _rss.reserve(capa);
    }

    //读文件
    void read(const string &filename)
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
    void store(const string &filename)
    {
        ofstream ofs(filename);
        if(!ofs)
        {
            std::cerr << "open " << filename << " fail!" << endl;
            return;
        }

        for(size_t idx = 0; idx != _rss.size(); ++idx)
        {
            ofs << "<doc>\n\t<docid>" << idx + 1
                << "</docid>\n\t<title>" << _rss[idx]._title 
                << "</title>\n\t<link>" << _rss[idx]._link 
                << "</description>\n\t<content>" << _rss[idx]._content << "</content>\n</doc>";
            ofs << '\n';
        }

        ofs.close();
    }
private:
    vector<RSSIteam> _rss;
};


void test0(){
    RSS rss(4000);
    rss.read("auto.xml");
    rss.store("pagelib.dat");
}

int main(void)
{
    test0();
    return 0;
}
