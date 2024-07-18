#include "ShaderUtils.h"

std::string ReadFile(const char* filePath) {
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream.is_open()) {
        std::cerr << "Failed to read file: " << filePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    fileStream.close();
    return buffer.str();
}
