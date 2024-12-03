//
// Created by rejamoto on 12/2/24.
//

#ifndef DAY_01_H
#define DAY_01_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>

class Day_01
{
public:
    Day_01 () = default;
    ~Day_01 () = default;

    void Run();

private:
    static void Console_WL(const std::string& str) { std::cout << str << std::endl; }
    static std::string TrimString(const std::string&str, const std::string& whitespace = " \t\r\n");

    const std::string DataFile { "../Day_01/Data.txt" };
    const std::string DataTestFile { "../Day_01/Data_Test.txt" };

    static void Solution_1(std::pair<std::vector<int>, std::vector<int>>& data);
    static void Solution_2(std::pair<std::vector<int>, std::vector<int>>& data);

    static std::pair<std::vector<int>, std::vector<int>> ReadData(const std::string& path);
};

#endif //DAY_01_H
