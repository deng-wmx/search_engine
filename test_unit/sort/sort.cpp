#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <queue>

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::priority_queue;

// 使用自定义仿函数进行排序
using PairType = pair<string, pair<int, int>>; 

struct Compare {
    bool operator()(const PairType &p1, const PairType &p2) {
        if (p1.second.first != p2.second.first) {
            return p1.second.first > p2.second.first; // 让 first 降序
        }
        return p1.second.second < p2.second.second; // 让 second 升序
    }
};

int main() {
    // 定义 priority_queue 时使用自定义比较函数
    priority_queue<PairType, std::vector<PairType>, Compare> queue;

    queue.push({"111", {2, 2}});
    queue.push({"222", {1, 2}});
    queue.push({"333", {2, 1}});

    // 遍历 priority_queue 并输出结果
    while(!queue.empty()) {
        auto val = queue.top();
        cout << val.first << " " << val.second.first << " " << val.second.second << "\n";
        queue.pop();
    }
    cout << "\n";

    return 0;
}

