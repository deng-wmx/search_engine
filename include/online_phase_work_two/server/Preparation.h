#ifndef __PREPARATION_H
#define __PREPARATION_H

#include <unordered_map>
#include <set>
#include <utility>
#include <string>

using std::unordered_map;
using std::unordered_map;
using std::set;
using std::pair;
using std::string;

class Preparation
{
public:
    Preparation();
    ~Preparation();
    void buildInvertedIndex();
    unordered_map<string, set<pair<int, double>>> getInvertedIndex() const;

private:
    unordered_map<string, set<pair<int, double>>> _invertedIndex; 
};

#endif
