
#include "FileManager.hpp"

int FileManager::readInt(std::ifstream& fptr) {
    uint8_t buffer[4];
    fptr.read(reinterpret_cast<char*>(buffer), 4);
    return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
}

std::vector<uint8_t> FileManager::loadMNISTLabels(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file " + filePath);
    }

    int magicNumber = readInt(file);
    int numLabels = readInt(file);

    std::vector<uint8_t> labels(numLabels);

    file.read(reinterpret_cast<char*>(labels.data()), numLabels);

    return labels;
}


std::vector<std::vector<uint8_t>> FileManager::loadMNISTImages(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file " + filePath);
    }

    int magicNumber = readInt(file);

    int numImages = readInt(file);
    int numRows = readInt(file);
    int numCols = readInt(file);


    std::vector<std::vector<uint8_t>> images(numImages, std::vector<uint8_t>(numRows * numCols));

    for (int i = 0; i < numImages; ++i) {
        file.read(reinterpret_cast<char*>(images[i].data()), numRows * numCols);
    }

    return images;
}

