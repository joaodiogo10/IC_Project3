#include "FCM.h"
#include <iostream>

int main(int argc, char *argv[]){

    uint16_t input = 0;

    while(input != 1 && input != 2)
    {
        std::cout << "1 - Create new FCM from a text file" << std::endl;
        std::cout << "2 - Load FCM from a .fcm file" << std::endl;

        std::cin >> input;
    }   
  
    FCM fcm;
    std::string filePath;

    switch (input)
    {
    case 1:
        std::cout << "Order: ";
        std::cin >> input;
        fcm = FCM(input);

        std::cout << "File path: ";
        std::cin >> filePath;
        if(!fcm.loadFile(filePath))
        {
            std::cout << "Failed to load file!" << std::endl;
            return -1;
        }
        break;

    case 2:
        std::cout << "File path: ";
        std::cin >> filePath;
        if(!(filePath.substr(filePath.find_last_of(".") + 1) == "fcm")) {
            std::cout << "Invalid format!" << std::endl;
            return -1;
        }

        if(!fcm.loadFCM(filePath))
        {
            std::cout << "Failed to load file!" << std::endl;
            return -1;
        }
        break;
    }

    while(true)
    {
        std::cout << "\n1 - Collect data from a file" << std::endl;
        std::cout << "2 - Get model entropy" << std::endl;
        std::cout << "3 - Save FCM to file" << std::endl;
        std::cout << "4 - Save FCM in readable format to file" << std::endl;
        std::cout << "5 - Quit" << std::endl;
        std::cin >> input;

        switch(input)
        {
            case 1:
                std::cout << "File path: ";
                std::cin >> filePath;

                if(!fcm.loadFile(filePath))
                    std::cout << "Failed to load file!" << std::endl;
                break;

            case 2:
                std::cout << "Entropy: " << fcm.modelEntropy() << std::endl;
                break;

            case 3:
                std::cout << "File path: ";
                std::cin >> filePath;

                if(!fcm.saveFCM(filePath))
                    std::cout << "Failed to save file!" << std::endl;
                break;

            case 4:
                std::cout << "File path: ";
                std::cin >> filePath;

                if(!fcm.printToFile(filePath))
                    std::cout << "Failed to save file!" << std::endl;
                break;

            case 5:
                return 0;
                break;
        }
    }  
    return 0;
}

