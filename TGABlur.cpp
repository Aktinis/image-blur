#include "TGABlur.h"
#include "BlurHelper.h"
#include "IOHandler.h"

std::vector<unsigned char> TGABlur::BlurImage(const TGAHeader& header, const std::vector<unsigned char>& imageData, const float blur)
{
    if (header.imageType != 2) {
        std::cerr << "Error: Only uncompressed true-color images are supported." << std::endl;
        return imageData;
    }

    if (header.bitsPerPixel != 24 && header.bitsPerPixel != 32)
    {
        std::cout << "No support for " << header.bitsPerPixel << "bit images" << std::endl;
        return imageData;
    }

    return Blur(header, imageData, blur, header.bitsPerPixel / 8);
}

std::vector<unsigned char> TGABlur::Blur(const TGAHeader& header, const std::vector<unsigned char>& imageData, const float blur, const int channelCount)
{
    int width = header.width;
    int height = header.height;
    int convertedBlur = (int)(blur * 100);

    std::vector<unsigned char> targetImageData(imageData.size());
    int size = imageData.size();

    std::vector<std::vector<unsigned char>> colorChannels;
    std::vector<std::vector<unsigned char>> targetColorChannels;

    for (int i = 0; i < channelCount; i++)
    {
        colorChannels.push_back(std::vector<unsigned char>(size / channelCount));
        targetColorChannels.push_back(std::vector<unsigned char>(size / channelCount));
    }

    int pixelIndex = 0;
    int index = 0;
    for (int y = 0; y < header.height; ++y) {
        for (int x = 0; x < header.width; ++x) {
            for (auto& channel : colorChannels)
            {
                channel[index] = imageData[pixelIndex++];
            }
            index++;
        }
    }

   for(int i = 0; i < channelCount; i++)
   {
        BlurHelper::GaussianAproximationBlur(colorChannels[i], targetColorChannels[i], header.width, header.height, convertedBlur);
   }
    pixelIndex = 0;
    index = 0;

    for (int y = 0; y < header.height; ++y) {
        for (int x = 0; x < header.width; ++x) {
            for (auto& channel : targetColorChannels)
            {
                targetImageData[pixelIndex++] = channel[index];
            }
            index++;
        }
    }

    return targetImageData;
}
