#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>

/** \file
 *  FCM class header file
 */

/**
 * \brief Class used to collect high-order statistical information of an information source 
 * 
 */

class FCM {
    public:
        /**
         * \brief Construct a new FCM object with order 0
         * 
         */
        FCM();

        /**
         * \brief Construct a new FCM object
         * \param[in] order order of the model
         * 
         */
        FCM(uint8_t order);
        
        /**
         * \brief Get the Order from the FCM class
         * 
         * \return Order of FCM class 
         */
        uint8_t getOrder();

        /**
         * \brief Get the number of times that a context of strings appears on a file 
         * 
         * \param[in] context String of chars 
         * \return Number of times the string of chars appears on the map
         */
        uint64_t getContextCount(const std::string context);

        /**
         * \brief Get the number of combinations for a context of strings from a Map
         * 
         * \param[in] context String of chars 
         * \return Map of all possible combinations for that context of strings
         */
        std::map<char, uint64_t> getMapContext(const std::string context);

        /**
         * \brief Loads FCM table
         * 
         * \param[in] filePath Path of FCM table
         * \return True if file is readable, False if it isn't
         */
        bool loadFCM(std::string filePath);

        /**
         * \brief Saves data from FCM class to a file
         * 
         * \param[in] filePath Path of file to save
         * \return True if it saved succesfully, False if not  
         */
        bool saveFCM(std::string filePath);

        /**
         * \brief Loads data from a text file
         * 
         * \param[in] filePath Path of text file
         * \return True if file is readable, False if it isn't 
         */
        bool loadFile(std::string filePath);

        /**
         * \brief Prints data of FCM to a text file in a readable manner
         * 
         * \param[in] filePath Path of file
         * \return True if file was saved successfully, False if not  
         */
        bool printToFile(std::string filePath);

        /**
         * \brief Calculate entropy of the FCM class
         * 
         * \return Entropy of the model
         */
        double modelEntropy();
        

        double estimateTotalBits(const std::string filePath, const double alpha, uint64_t &totalCharacters);


    private:
        uint8_t order;
        uint64_t totalMatches;

        std::map<std::string, std::map<char, uint64_t>> mapContext;
        std::map<std::string, uint64_t> contextCount;

        //std::vector<std::string> getAllContexts(uint8_t order);
        //std::vector<std::string> getAllContexts(std::vector<std::string> strings, uint8_t order);

        //void initializeMap(std::map<std::string, std::map<char, uint32_t>>& mapContext, uint8_t order);
};