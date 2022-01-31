#include "FCM.h"
#include "dirent.h"
#include <fstream>
#include <iostream>
#include <limits>

bool listFiles(const std::string directoryModels, const int order, std::vector<std::string> &fileVector);
std::string getLanguageFromFile(const std::string fileName);

int main(int argc, char *argv[]){
    std::string testFilePath; 
    std::string directoryModels;
    std::vector<std::string> modelFileList;
    
    double alpha;
    int order;

    if(argc < 5 || std::stoi(argv[4]) < 0 ) {
        std::cout << "Usage: ./findlang <modelsDirectoryPath> <testFilePath> <alpha> <order>" << std::endl;
        return -1;
    }
    directoryModels = std::string(argv[1]) + "/Order_" + std::string(argv[4]);
    testFilePath = argv[2];
    alpha = std::stod(argv[3]);
    order = std::stoi(argv[4]);

    std::cout << "Alpha: " << alpha << std::endl;
    std::cout << "Order: " << order << std::endl;


    if(!listFiles(directoryModels, order, modelFileList)) {
        std::cout << "Invalid models directory path!" << std::endl;
        return -1;
    }

    double bestTotalBits = std::numeric_limits<double>::max(); 
    std::string bestLanguage = "";

    uint64_t totalCharacters = 0;

    double modelEntropy = 0;
    //Test text file for each model
    for(std::string modelFile : modelFileList) {
        FCM fcm = FCM();

        std::string language = getLanguageFromFile(modelFile);
        std::string modelFilePath = directoryModels + "/" + modelFile;

        if(!fcm.loadFCM(modelFilePath)) {
            std::cout << "Failed to load model from file \"" << modelFilePath << "\" !" << std::endl;
            continue;
        }
        
        double totalBits = fcm.estimateTotalBits(testFilePath, alpha, totalCharacters);
        if(totalBits < 0) {
            std::cout << "Failed to open test file!" << std::endl;
            return -1;
        }

        if(bestTotalBits > totalBits) {
            bestTotalBits = totalBits;
            bestLanguage = language;
            modelEntropy = fcm.modelEntropy();
        }

        //std::cout << "\n\nLanguage: " << language << std::endl;
        //std::cout << "Bits per character: " << totalBits / totalCharacters << std::endl;
    }
    std::cout << "\n\n--------Best Result--------" << std::endl;
    std::cout << "Language: " << bestLanguage << std::endl;
    std::cout << "Total bits: " << bestTotalBits << std::endl;
    std::cout << "Total characters: " << totalCharacters << std::endl;
    std::cout << "Model entropy: " << modelEntropy << std::endl;
    std::cout << "Bits per character: " << bestTotalBits / totalCharacters << std::endl;
    
    return 0;
}

bool listFiles(const std::string modelsDirectory, int order, std::vector<std::string> &fileVector) {
    DIR *dir;
    struct dirent *ent;
    std::string directory; 

    if ((dir = opendir(modelsDirectory.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            std::string fileName(ent->d_name);
            if(fileName.substr(fileName.find_last_of(".") + 1) == "fcm")
                fileVector.push_back(fileName);
        }
        
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return false;
    }

    return true;
}

std::string getLanguageFromFile(const std::string fileName) {
    return fileName.substr(0, fileName.find_last_of("."));
}
