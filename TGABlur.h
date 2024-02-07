#pragma once
#include <iostream>
#include <fstream>
#include <vector>


#pragma pack(push, 1)
struct TGAHeader {
    char idLength;
    char colorMapType;
    char imageType;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOffset;
    short yOffset;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};
#pragma pack(pop)

class TGABlur
{
public:
    static std::vector<unsigned char> BlurImage(const TGAHeader& header, const std::vector<unsigned char>& imageData, const float blur);

private:
    static std::vector<unsigned char> Blur(const TGAHeader& header, const std::vector<unsigned char>& imageData, const float blur, const int channelCount);
};

