#include "FileReader.h"

using namespace FileAccess;

FileReader::FileReader(const std::string& path) {
    stream = std::ifstream(path);
    stream.rdbuf()->pubsetbuf(buffer, bufferSize);
}

FileReader::~FileReader() {
    stream.close();
}

char FileReader::getch() {
    if (!stack.empty()) {
        auto c = stack.top();
        stack.pop();
        if (c == '\n') {
            line++;
            linePos = 0;
        } else {
            linePos++;
        }
        return c;
    }
    char c;
    stream.get(c);
    if (c == '\n') {
        line++;
        linePositions.push_back(linePos);
        linePos = 0;
    } else {
        linePos++;
    }
    return c;
}

void FileReader::putch(char c) {
    stack.push(c);
    if (c == '\n') {
        line--;
        linePos = linePositions[line];
    } else {
        linePos--;
    }
}

bool FileReader::good() {
    return stream.good();
}

uint32_t FileReader::getLine() {
    return line;
}

uint32_t FileReader::getLinePos() {
    return linePos;
}
