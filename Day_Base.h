//
// Created by rejamoto on 12/3/24.
//

#ifndef DAY_BASE_H
#define DAY_BASE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>

class Day_Base
{
protected:
    std::string DataFile;
    std::string DataFile2;
    std::string DataTestFile;
    std::string DataTestFile2;

    static void Console_WL(const std::string& str) { std::cout << str << std::endl; }
    static std::string TrimString(const std::string&str, const std::string& whitespace = " \t\r\n")
    {
        const size_t strBeginIndex = str.find_first_not_of(whitespace);

        if (strBeginIndex == std::string::npos) return "";

        const size_t strEndIndex = str.find_last_not_of(whitespace);
        const size_t strRange = strEndIndex - strBeginIndex + 1;

        return str.substr(strBeginIndex, strRange);
    }
};

#endif //DAY_BASE_H
