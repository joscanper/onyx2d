#ifndef GEN_FUNC_H
#define GEN_FUNC_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include "../../onyx2d_defs.h"

#define PI 3.1415926536

using namespace std;

namespace onyx2d
{
    /**
    * Function that returns if the file exist
    * @param path Path of the file.
    * @return <i>true</i> if the file exist, <i>false</i> in other case.
    **/
    bool FileExist(std::string path);

    /**
    * Function that returns a file extension
    * @param path Path of the file.
    * @return Extension of the file.
    **/
    std::string FileExtension(std::string path);

    /**
    * Function that returns a random double number
    * @param low Low number of the range
    * @param high High number of the range
    * @return Random number generated.
    **/
    double Randomd(double low, double high);


    /**
    * Function that returns a random integer number
    * @param low Low number of the range
    * @param high High number of the range
    * @return Random number generated.
    **/
    int32 Random(int32 low, int32 high);

    /**
    * Function that convert grads to radians
    * @param grads Grads number to convert
    * @return Radians number
    **/
    double ToRads(int16 grads);

    /**
    * Function that convert radians to grads
    * @param rads Radians number to convert
    * @return Grads number
    **/
    int16 ToGrads(double rads);

    /**
    * Function that split a string by a specific delimitator
    * @param str String to split
    * @param delim Delimitators
    * @return Vector of strings with the start string splitted
    **/
    std::vector<std::string> StringSplit(std::string str, std::string delim);

    /**
    * Function that convert a string to lower case
    * @param str String to convert
    * @return String converted
    **/
    std::string StringToLower(std::string myString);

    /**
    * Function that convert a string to upper case
    * @param str String to convert
    * @return String converted
    **/
    std::string StringToUpper(std::string myString);

}

#endif
