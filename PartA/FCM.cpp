#include <iostream>
#include <fstream>
#include <math.h>
#include "FCM.h"

FCM::FCM(uint8_t order){
    this->order = order;
    initializeMap(mapContext, order);

}

void FCM::initializeMap(std::map<std::string, std::map<char, uint32_t>>& mapContext, uint8_t order) {
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
}

void FCM::printToFile(std::map<std::string, std::map<char, uint32_t>>& mapContext,std::map<std::string,uint32_t>& totalCount,std::string fileName) {
    std::ofstream outputFile;
    outputFile.open(fileName);

    uint32_t total = 0;
    for(const auto pairContext: mapContext) {
        total += totalCount[pairContext.first];
        std::map<char, uint32_t> mapCount = pairContext.second;
        for(const auto pairCount: mapCount) {
            outputFile << pairContext.first << " " << pairCount.first << ": " << pairCount.second << std::endl; 
        }
        outputFile << "------Total------\n" << totalCount[pairContext.first] << std::endl;  
    } 

    outputFile << "Total:" << total << std::endl;
    outputFile.close();
}

bool FCM::loadFile(std::string fileName){
    std::ifstream inputFile;
    inputFile.open(fileName, std::ios::in);
    if(!inputFile) {
        std::cout << "Failed to open file \"" << fileName  << "\""<< std::endl;
        return false;
    }
    std::cout << "can read file" << std::endl;
    char context[order];
    //context initially starts with 'a's
    for(int i = 0; i < order; i++) {
        context[i] = 'a';
    }

    char nextChar = '\0';
    while(inputFile >> nextChar) {
        nextChar = tolower(nextChar);

        std::cout << "a" << std::endl;
        if(std::isalpha(nextChar)) {
            std::string strContext(context, order);
            totalCount[strContext]++;
            mapContext[strContext][nextChar]++;
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

bool FCM::saveFile(std::string fileName){
    std::ofstream outputFile;
    outputFile.open(fileName);

    for(const auto pairContext: mapContext) {
        std::map<char, uint32_t> mapCount = pairContext.second;
        for(const auto pairCount: mapCount) {
            outputFile << pairContext.first << " " << pairCount.first << " " << pairCount.second << std::endl; 
        } 
    }

    outputFile.close();
    return true; 
}

uint32_t FCM::modelTotalCount(std::map<std::string, uint32_t> &totalCount)
{
    uint32_t tCount = 0;
    for (auto const &counts : totalCount)
    {
        tCount += counts.second;
    }

    return tCount;
}

void FCM::subModelEntropy(std::map<std::string, std::map<char, uint32_t>> &mapContext, std::map<std::string, uint32_t> &totalCount, std::map<std::string, double> &mapSubModelEntropy)
{
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
}

void FCM::subModelProb(std::map<std::string, std::map<char, uint32_t>> &mapContext, std::map<std::string, uint32_t> &totalCount, std::map<std::string, double> &mapSubModelProb){
    uint32_t tCount = modelTotalCount(totalCount);

    for (auto const &context : mapContext)
    {
        std::string currentContext = context.first;

        mapSubModelProb[currentContext] = double(totalCount[currentContext]) / tCount;
    }
}