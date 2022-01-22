#include <map>
#include <vector>

class FCM {
    public:
        FCM(uint8_t order);

        bool saveFile(std::string fileName);
        bool loadFile(std::string fileName);
        void printToFile(std::map<std::string, std::map<char, uint32_t>>& mapContext,std::map<std::string,uint32_t>& totalCount,std::string fileName);
        void subModelEntropy(std::map<std::string, std::map<char, uint32_t>> &mapContext, std::map<std::string, uint32_t> &totalCount, std::map<std::string, double> &mapSubModelEntropy);
        void subModelProb(std::map<std::string, std::map<char, uint32_t>> &mapContext, std::map<std::string, uint32_t> &totalCount, std::map<std::string, double> &mapSubModelProb);

        std::map<std::string, std::map<char, uint32_t>> mapContext;
        std::map<std::string, uint32_t> totalCount;
        std::map<std::string, double> mapSubModelEntropy;
        std::map<std::string, double> mapSubModelProb;
        
    private:

        uint8_t order;
        std::vector<std::string> getAllContexts(uint8_t order);
        std::vector<std::string> getAllContexts(std::vector<std::string> strings, uint8_t order);
        

        void initializeMap(std::map<std::string, std::map<char, uint32_t>>& mapContext, uint8_t order);
        uint32_t modelTotalCount(std::map<std::string, uint32_t> &totalCount);
            
};