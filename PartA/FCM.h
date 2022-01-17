#include <map>
#include <vector>

class FCM {
    public:
        FCM(uint8_t order);

        void saveFile(std::string fileName);
        bool loadFile(std::string fileName);
        void printToFile(std::map<std::string, std::map<char, uint32_t>>& mapContext,std::map<std::string,uint32_t>& totalCount,std::string fileName);
        
    private:

        uint8_t order;
        std::vector<std::string> getAllContexts(uint8_t order);
        std::vector<std::string> getAllContexts(std::vector<std::string> strings, uint8_t order);
        
        std::map<std::string, std::map<char, uint32_t>> mapContext;
        std::map<std::string, uint32_t> totalCount;

        void initializeMap(std::map<std::string, std::map<char, uint32_t>>& mapContext, uint8_t order);
            
};