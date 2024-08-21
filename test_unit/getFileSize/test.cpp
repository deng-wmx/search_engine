#include <iostream>
#include <fstream>
using std::ifstream;

long getFileSize(const std::string& filename) {
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

int main() {
    std::string filename = "example.dat";

    // 打开文件并写入内容
    /* { */
    /*     std::ofstream ofs(filename, std::ios::app); */
    /*     if (ofs.is_open()) { */
    /*         ofs << "Hello, World!"; */
    /*         ofs.close(); */
    /*     } else { */
    /*         std::cerr << "Unable to open file for writing: " << filename << std::endl; */
    /*     } */
    /* } */

    // 获取文件长度
    long fileSize = getFileSize(filename);
    if (fileSize != -1) {
        std::cout << "File size: " << fileSize << " bytes" << std::endl;
    }

    return 0;
}

