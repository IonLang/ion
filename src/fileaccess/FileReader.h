#pragma once

#include <fstream>
#include <stack>
#include <vector>

namespace FileAccess {

class FileReader {
public:
    FileReader(const std::string& path);
    ~FileReader();

    char getch();
    void putch(char c);
    bool good();

    uint32_t getLine();
    uint32_t getLinePos();

private:
    static constexpr int bufferSize = 4096;
    char buffer[bufferSize];
    std::ifstream stream;
    std::stack<char> stack;
    uint32_t line = 0;
    uint32_t linePos = 0;
    std::vector<uint32_t> linePositions;
};

}
