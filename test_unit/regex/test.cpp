#include <boost/regex.hpp>
#include <iostream>
#include <string>

std::string filter_text(const std::string& input) {
    // 仅保留英文字符、英文标点符号、中文字符和中文标点符号
    // 注意使用 Boost 正则表达式库的 \p{L} 和 \p{P} 支持
    boost::regex reg("[^a-zA-Z0-9\\p{L}\\p{P}\\p{S}]");

    // 替换掉不符合要求的字符
    std::string filtered = boost::regex_replace(input, reg, "");
    return filtered;
}

int main() {
    std::string content = "Hello, 世界! 1234 @#$%^&*()";
    std::string filtered_content = filter_text(content);
    std::cout << "Filtered content: " << filtered_content << std::endl;
    return 0;
}

