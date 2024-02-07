#pragma once
#include <string>
#include <vector>

class IOHandler
{
public:
	template<typename T>
	static bool ReadImageFile(T& header, const std::string& filename, std::vector<unsigned char>& imageData) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Failed to open file: " << filename << std::endl;
            return false;
        }

        file.read(reinterpret_cast<char*>(&header), sizeof(T));

        int width = header.width;
        int height = header.height;
        int bytesPerPixel = header.bitsPerPixel / 8;
        imageData.resize(width * height * bytesPerPixel);
        file.read(reinterpret_cast<char*>(imageData.data()), imageData.size());
        file.close();

        return true;
	}

    template<typename T>
    static bool WriteImageFile(const T& header, const std::string& filename, const std::vector<unsigned char>& imageData)
    {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Failed to open file for writing: " << filename << std::endl;
            return false;
        }

        file.write(reinterpret_cast<const char*>(&header), sizeof(T));

        file.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());

        file.close();
        return true;
    }
};

