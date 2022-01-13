#include <iostream>
#include <fstream>
#include <map>

int main(int argc, char* argv[]) {

    std::ifstream inputFile;
    inputFile.open("lusiadas.txt", std::ios::in);

    char result = '\0';

    std::map<char, int> mapCharacters;

    while(inputFile >> result)
        if(std::isalpha(result)) {
            mapCharacters[std::tolower(result)]++;
        }
    
    for(const auto pair: mapCharacters) {
        std::cout << pair.first << ": " << pair.second << std::endl; 
    }

    std::cout << mapCharacters.size() << std::endl;
    inputFile.close();
    return 0;
}