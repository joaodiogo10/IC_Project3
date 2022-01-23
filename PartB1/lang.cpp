#include "FCM.h"
#include <fstream>
#include <iostream>
#include <cmath>

double alpha = 0.5;

int main(int argc, char *argv[]){
    
    std::string modelFilePath; 
    std::string testFilePath; 
    double alpha;

    if(argc < 4) {
        std::cout << "Usage: ./lang <modelFilePath> <testFilePath> <alpha>";
    }

    modelFilePath = argv[1];
    testFilePath = argv[2];
    alpha = std::stod(argv[3]);
    std::cout << "Alpha: " << alpha << std::endl;

    std::ifstream testFile;
    testFile.open(testFilePath, std::ios::in);
    if(!testFile) {
        std::cout << "Failed to open test file!" << std::endl;
        return -1;
    }

    FCM fcm = FCM();
    if(!fcm.loadFCM(modelFilePath)) {
        std::cout << "Failed to load model!" << std::endl;
        return -1;
    }

    uint8_t order = fcm.getOrder();
    char context[order];
 
    //context initially starts with 'a's
    for(int i = 0; i < order; i++) {
        context[i] = 'a';
    }

    double totalBits = 0;
    char nextChar = '\0';
    uint32_t totalCharacters = 0;
    while(testFile >> nextChar) {
        nextChar = tolower(nextChar);
        if(std::isalpha(nextChar)) {
            std::string strContext(context, order);
            
            std::map<char, uint64_t> mapContext = fcm.getMapContext(strContext);
            uint64_t contextCount = fcm.getContextCount(strContext);

            uint64_t entry = mapContext[nextChar];
            uint32_t nUniqueEntries = mapContext.size();

            totalBits -= std::log2((entry + alpha) / (double(contextCount) + alpha * nUniqueEntries));
            //update context        
            for(int i = 1; i < order; i++) {
                context[i-1] = context[i];
            }
            context[order-1] = nextChar;
        }
        totalCharacters++;
    }

    std::cout << "Total bits: " << totalBits << std::endl;
    std::cout << "Total characters: " << totalCharacters << std::endl;
    std::cout << "Bits per character: " << totalBits / totalCharacters << std::endl;
    std::cout << "Model entropy: " << fcm.modelEntropy() << std::endl;
    testFile.close();
    
    return 0;
}