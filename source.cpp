#include "TGABlur.h"
#include <string>
#include "IOHandler.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <path1> <path2> <float_value>" << std::endl;
        return 1;
    }

    std::string inputFilePath = argv[1];
    std::string outputFilePath = argv[2];
    float floatValue = std::stof(argv[3]); 

    TGAHeader header;
    std::vector<unsigned char> imageData;


    if (IOHandler::ReadImageFile(header, inputFilePath, imageData)) {
        std::cout << "TGA file successfully loaded." << std::endl;
    }

    std::vector<unsigned char> blurredImageData = TGABlur::BlurImage(header, imageData, floatValue);

    if (IOHandler::WriteImageFile(header, outputFilePath, blurredImageData))
    {
        std::cout << "TGA file successfully saved blurred image." << std::endl;
    }
    return 0; 
}