#include <iostream>
#include <fstream>
#include <map>
#include <vector>

std::vector<std::string> getAllContexts(uint8_t order);
std::vector<std::string> getAllContexts(std::vector<std::string> strings, uint8_t order);
void initializeMap(std::map<std::string, std::map<char, uint32_t>>& mapContext, uint8_t order);
void printToFile(std::map<std::string, std::map<char, uint32_t>>& mapContext, std::string fileName);

int main(int argc, char* argv[]) {
    if(argc < 3 || std::atoi(argv[2]) < 0) {
        std::cout << "Usage: ./fcm <inputFile> <order>" << std::endl;
        std::cout << "order should be >= 0" << std::endl;

        return -1;
    }
    std::string filePath = argv[1];
    uint16_t order = std::atoi(argv[2]);

    std::ifstream inputFile;
    inputFile.open(filePath, std::ios::in);
    if(!inputFile) {
        std::cout << "Failed to open file \"" << filePath  << "\""<< std::endl;
        return -1;
    }

    //initialize map with '1's to handle unmatched string sequences
    std::map<std::string, std::map<char, uint32_t>> mapContext;
    initializeMap(mapContext, order);

    char context[order];
    //context initially starts with 'a's
    for(int i = 0; i < order; i++) {
        context[i] = 'a';
    }

    //read file and count string sequences occurrence
    char nextChar = '\0';
    while(inputFile >> nextChar) {
        nextChar = tolower(nextChar);

        if(std::isalpha(nextChar)) {
            std::string strContext(context, order);

            mapContext[strContext][nextChar]++;
            //update context        
            for(int i = 1; i < order; i++) {
                context[i-1] = context[i];
            }
            context[order-1] = nextChar;
        }
    }
    
    printToFile(mapContext, "output.txt");
    
    inputFile.close();
    return 0;
}

void initializeMap(std::map<std::string, std::map<char, uint32_t>>& mapContext, uint8_t order) {
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

std::vector<std::string> getAllContexts(uint8_t order) {
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

std::vector<std::string> getAllContexts(std::vector<std::string> strings, uint8_t order) {
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

void printToFile(std::map<std::string, std::map<char, uint32_t>>& mapContext, std::string fileName) {
    std::ofstream outputFile;
    outputFile.open(fileName);

    for(const auto pairContext: mapContext) {
        std::map<char, uint32_t> mapCount = pairContext.second;
        for(const auto pairCount: mapCount) {
            outputFile << pairContext.first << " " << pairCount.first << ": " << pairCount.second << std::endl; 
        }
    } 

    outputFile.close();
}