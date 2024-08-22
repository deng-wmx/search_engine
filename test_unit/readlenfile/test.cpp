#include <iostream>
#include <fstream>
#include <vector>

int main() {
    // 打开文件
    std::ifstream file("/home/dengdeng/myfiles/search_engine/data/page.dat", std::ios::binary);
    
    if (!file) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    // 指定读取的起始位置和长度
    std::streampos position = 1041270;  // 从文件的第10个字节开始读取
    std::size_t length = 2546;       // 读取20个字节

    // 移动文件读取指针到指定位置
    file.seekg(position);

    // 创建一个缓冲区来存储读取的内容
    std::vector<char> buffer(length + 1);

    // 读取指定长度的内容到缓冲区
    file.read(buffer.data(), length);
    buffer.data()[length] = '\0';

    if (file) {
        std::cout << "读取成功，共读取了 " << file.gcount() << " 字节。" << std::endl;
    } else {
        std::cerr << "读取过程中出现错误。" << std::endl;
    }
    std::cout << buffer.data();

    // 关闭文件
    file.close();

    // 处理读取的内容，例如输出到控制台
    /* std::cout << "读取的内容是：" << std::endl; */
    /* for (char c : buffer) { */
    /*     std::cout << c; */
    /* } */
    /* std::cout << std::endl; */

    return 0;
}

