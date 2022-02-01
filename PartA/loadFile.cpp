#include "FCM.h"
#include <iostream>
#include <fstream>
#include <sstream>

/** \file
 *  File to create a FCM from a text.
 */

/**
 * \brief
 * Usage: ./loadFile FCMName order textFile \n
 * 
 * Given the name of the output file (FCM) and the order, it generates
 * the context model from the given textFile.
 * 
 */

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

    if (!fcm.saveFCM(FCMName))
        std::cout << "Failed to save file!" << std::endl;

    return 0;
}
