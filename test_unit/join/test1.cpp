#include <iostream>
#include "../../include/online_phase_work/nlohmann/json.hpp"

int main() {
    // JSON字符串
    std::string json_str = R"(["animal","final","ha","hat","hay","naval","nice","night","nina","ohio"])";

    // 解析JSON字符串
    nlohmann::json json_array = nlohmann::json::parse(json_str);

    // 输出JSON数组中的元素
    for (const auto& element : json_array) {
        std::cout << element.get<std::string>() << std::endl;
    }

    return 0;
}

