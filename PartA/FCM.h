#include <map>
#include <vector>

class FCM {
    public:
        FCM();
        FCM(uint8_t order);
        
        bool loadFCM(std::string filePath);
        bool saveFCM(std::string filePath);

        bool loadFile(std::string filePath);
        bool printToFile(std::string filePath);
        double modelEntropy();
        
    private:
        uint8_t order;
        uint64_t totalMatches;

        std::map<std::string, std::map<char, uint64_t>> mapContext;
        std::map<std::string, uint64_t> totalCount;

        //std::vector<std::string> getAllContexts(uint8_t order);
        //std::vector<std::string> getAllContexts(std::vector<std::string> strings, uint8_t order);

        //void initializeMap(std::map<std::string, std::map<char, uint32_t>>& mapContext, uint8_t order);
};