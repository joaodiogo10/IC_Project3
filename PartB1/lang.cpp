#include "FCM.h"
#include <fstream>
#include <iostream>
#include <cmath>

/** \file
 *  lang
 */

int main(int argc, char *argv[]){
        std::string modelFilePath; 
    std::string testFilePath; 
    double alpha;

    if(argc < 4) {
        std::cout << "Usage: ./lang <modelFilePath> <testFilePath> <alpha>" << std::endl;
        return -1;
    }

    modelFilePath = argv[1];
    testFilePath = argv[2];
    alpha = std::stod(argv[3]);
    std::cout << "Alpha: " << alpha << std::endl;

    FCM fcm = FCM();
    if(!fcm.loadFCM(modelFilePath)) {
        std::cout << "Failed to load model!" << std::endl;
        return -1;
    }
    
    uint64_t totalCharacters = 0;
    double totalBits = fcm.estimateTotalBits(testFilePath, alpha, totalCharacters);
    if(totalBits < 0) {
        std::cout << "Failed to open test file!" << std::endl;
        return -1;
    }


    std::cout << "Total bits: " << totalBits << std::endl;
    std::cout << "Total characters: " << totalCharacters << std::endl;
    std::cout << "Bits per character: " << totalBits / totalCharacters << std::endl;
    std::cout << "Model entropy: " << fcm.modelEntropy() << std::endl;
    
    return 0;
}