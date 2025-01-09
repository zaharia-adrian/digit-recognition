#pragma once

#include <fstream>
#include <vector>

class FileManager {
	static int readInt(std::ifstream &);
public:
	static std::vector<uint8_t> loadMNISTLabels(const std::string&);
	static std::vector<std::vector<uint8_t>> loadMNISTImages(const std::string&);

};