#include "FCM.h"
#include <iostream>

int main(int argc, char *argv[]){
    if (argc < 3 || std::atoi(argv[2]) < 0)
    {
        std::cout << "Usage: ./fcm <inputFile> <order>" << std::endl;
        std::cout << "order should be >= 0" << std::endl;

        return -1;
    }

    std::string filePath = argv[1];
    uint8_t order = std::atoi(argv[2]);
    FCM fcm(order);

    fcm.loadFile(filePath);
    std::cout << "loadFile done" << std::endl;

    fcm.printToFile(fcm.mapContext, fcm.totalCount, "readableOutput.txt");
    std::cout << "printFile done" << std::endl;

    fcm.subModelEntropy(fcm.mapContext, fcm.totalCount, fcm.mapSubModelEntropy);
    std::cout << "subModelEntropy done" << std::endl;
    fcm.subModelProb(fcm.mapContext, fcm.totalCount, fcm.mapSubModelProb);
    std::cout << "subModeProb done" << std::endl;

    double modelEntropy = 0;

    for (auto const &mapEntropy : fcm.mapSubModelEntropy)
    {
        modelEntropy += mapEntropy.second * fcm.mapSubModelProb[mapEntropy.first];
    }

    std::cout << "Model entropy: " << modelEntropy << std::endl;

    fcm.saveFile("dataOutput.txt");
    return 0;
}