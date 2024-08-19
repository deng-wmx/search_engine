#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

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

int main() {
    string str = "@dafhl你好%";

    for (size_t i = 0; i < str.size();) {
        size_t len = nBytescode(static_cast<unsigned char>(str[i]));
        if (len == 0) {
            cout << "Invalid UTF-8 character\n";
            break;
        }
        cout << str.substr(i, len) << "\n";
        i += len;
    }

    return 0;
}

