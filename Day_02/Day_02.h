//
// Created by rejamoto on 12/2/24.
//

#ifndef DAY_02_H
#define DAY_02_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>

class Day_02
{
public:
    Day_02 () = default;
    ~Day_02 () = default;

    void Run() const;

private:
    static void Console_WL(const std::string& str) { std::cout << str << std::endl; }
    static std::string TrimString(const std::string&str, const std::string& whitespace = " \t\r\n");

    const std::string DataFile { "../Day_02/Data.txt" };
    const std::string DataTestFile { "../Day_02/Data_Test.txt" };
    const std::pair<int, int> Tolerances = { 1, 3 };

    void Solution_1(std::vector<std::vector<int>>& data) const;
    void Solution_2(std::vector<std::vector<int>>& data) const;

    [[nodiscard]] bool CheckReport(const std::vector<int>& reportNumbers, const int &indexSkip = -1) const;

    static std::vector<std::vector<int>> ReadData(const std::string& path);
};

#endif //DAY_02_H
