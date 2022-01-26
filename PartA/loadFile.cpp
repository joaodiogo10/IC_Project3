#include "FCM.h"
#include <iostream>
#include <fstream>
#include <sstream>

// ./loadFile FCM order textFile
int main(int argc, char *argv[])
{
    std::string FCMName = argv[1];
    std::string textFile = argv[3];
    int order;
    std::istringstream myStringOrder((std::string)argv[2]);
    myStringOrder >> order;

    FCM fcm;
    fcm = FCM(order);
    if (!fcm.loadFile(textFile))
    {
        std::cout << "Failed to load file!" << std::endl;
        return -1;
    }

    std::string finalPath = FCMName + "_" + (std::string)argv[2];

    if (!fcm.saveFCM(finalPath))
        std::cout << "Failed to save file!" << std::endl;

    return 0;
}
