#include <iostream>
#include <fstream>
#include <math.h>
#include "FCM.h"

FCM::FCM() {
    this->order = 0;
    this->totalMatches = 0;
}

FCM::FCM(uint8_t order) {
    this->order = order;
    this->totalMatches = 0;
}

bool FCM::loadFile(std::string filePath){
    std::ifstream inputFile;
    inputFile.open(filePath, std::ios::in);
    if(!inputFile) 
        return false;

    char context[order];
    //context initially starts with 'a's
    for(int i = 0; i < order; i++) {
        context[i] = 'a';
    }

    char nextChar = '\0';
    while(inputFile >> nextChar) {
        nextChar = tolower(nextChar);
        if(std::isalpha(nextChar)) {
            std::string strContext(context, order);

            if(totalCount.count(strContext) == 0)
            {
                totalCount[strContext] = 1;
                mapContext[strContext][nextChar] = 1;
            }
            else
            {
                totalCount[strContext]++;
                mapContext[strContext][nextChar]++;
            }
            totalMatches++;

            //update context        
            for(int i = 1; i < order; i++) {
                context[i-1] = context[i];
            }
            context[order-1] = nextChar;
        }
    }

    inputFile.close();

    return true;
}

bool FCM::loadFCM(std::string filePath) {
    std::ifstream inputFile;
    inputFile.open(filePath);
    if(!inputFile) 
        return false;
    
    bool success = true;
    if(!(inputFile >> totalMatches))
        success = false;

    std::string context;
    char c;
    uint64_t total;

    while(inputFile.peek() != EOF) {
        if(!(inputFile >> context)) success = false;
        if(!(inputFile >> c)) success = false;
        if(!(inputFile >> total)) success = false;
        
        if(totalCount.count(context) == 0)
            totalCount[context] = 0;

        totalCount[context] += total;
        mapContext[context][c] = total;

        inputFile.get();
    }

    order = context.size();
    inputFile.close();
    return success;
}   

bool FCM::saveFCM(std::string filePath) {
    std::ofstream outputFile;
    std::string file = filePath;
    if(!(filePath.substr(filePath.find_last_of(".") + 1) == "fcm"))
        file += ".fcm";

    outputFile.open(file);

    if(!outputFile) 
        return false;

    outputFile << totalMatches << std::endl;
    for(const auto pairContext: mapContext) {
        std::map<char, uint64_t> mapCount = pairContext.second;
        for(const auto pairCount: mapCount) {
            outputFile << pairContext.first << " " << pairCount.first << " " << pairCount.second << std::endl; 
        } 
    }

    outputFile.close();
    return true; 
}

double FCM::modelEntropy() {
    std::map<std::string, double> mapSubModelEntropy;
    
    //calculate submodel entropy
    for (auto const &context : mapContext)
    {
        std::string currentContext = context.first;
        double entropy = 0;

        for (auto const &symbols : context.second)
        {
            double prob = 0;

            if (totalCount[currentContext] != 0)
            {
                prob = symbols.second / double(totalCount[currentContext]);
            }

            if (prob != 0)
            {
                entropy += prob * log2(prob);
            }
        }

        mapSubModelEntropy[currentContext] = -entropy;
    }


    //calculate submodel probability
    std::map<std::string, double> mapSubModelProb;

    for (auto const &context : mapContext)
    {
        std::string currentContext = context.first;

        mapSubModelProb[currentContext] = double(totalCount[currentContext]) / totalMatches;
    }

    //finally calculate model entropy
    double modelEntropy = 0;
    for (auto const &mapEntropy : mapSubModelEntropy)
    {
        modelEntropy += mapEntropy.second * mapSubModelProb[mapEntropy.first];
    }

    return modelEntropy;
}

bool FCM::printToFile(std::string filePath) {
    std::ofstream outputFile;
    outputFile.open(filePath);
    if(!outputFile) 
        return false;

    uint32_t total = 0;
    for(const auto pairContext: mapContext) {
        total += totalCount[pairContext.first];
        std::map<char, uint64_t> mapCount = pairContext.second;
        for(const auto pairCount: mapCount) {
            outputFile << pairContext.first << " " << pairCount.first << ": " << pairCount.second << std::endl; 
        }
        outputFile << "------Total------\n" << totalCount[pairContext.first] << std::endl;  
    } 

    outputFile << "Total:" << total << std::endl;
    outputFile.close();
    return true;
}

/*void FCM::initializeMap(std::map<std::string, std::map<char, uint32_t>>& mapContext, uint8_t order) {
    std::vector<std::string> contexts = getAllContexts(order);

    //initialize map with '1's
    char alphaChar;
    for(ulong s = 0; s < contexts.size(); s++) {
        for(int i = 0; i < 26; i++) {
            alphaChar = (char) ((uint8_t) 'a' + i);
            mapContext[contexts[s]][alphaChar] = 1;
        }
    }
}

std::vector<std::string> FCM::getAllContexts(uint8_t order) {
    std::vector<std::string> strings;
    //0 order no context return empty vector
    if(order == 0)
        return strings;
    
    char alphaChar;
    for(int i = 0; i < 26; i++) {
        alphaChar = (char) ((uint8_t) 'a' + i);
        strings.push_back(std::string(1,alphaChar));
    }
    
    return getAllContexts(strings, order - 1);
}

std::vector<std::string> FCM::getAllContexts(std::vector<std::string> strings, uint8_t order) {
    if(order == 0)
        return strings;
    
    char alphaChar;
    std::vector<std::string> newStrings;
    for(u_long s = 0; s < strings.size(); s++) {
        for(int i = 0; i < 26; i++) {
            alphaChar = (char) ((uint8_t) 'a' + i);
            newStrings.push_back(strings[s] + alphaChar);
        }
    }
    return getAllContexts(newStrings, order - 1);
}*/