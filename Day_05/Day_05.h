//
// Created by rejamoto on 12/8/24.
//

#ifndef DAY_05_H
#define DAY_05_H

#include <map>

#include "../Day_Base.h"

class Day_05 : protected Day_Base
{
public:
    Day_05()
    {
        DataFile = "../Day_05/Data.txt";
        DataTestFile = "../Day_05/Data_Test.txt";
    }
    ~Day_05() = default;

    void Run() const;

private:
    std::map<int, bool> PrintedPages;

    class SafetyManual
    {
    public:
        std::vector<std::pair<int, int>> PageOrderRules;
        std::vector<std::vector<int>> PagesToPrint;
        std::vector<std::vector<int>> IncorrectUpdates;
    };

    static void Solution_1(SafetyManual& SafetyManual);
    static void Solution_2(SafetyManual& SafetyManual);

    static SafetyManual ReadData(const std::string& path);
};

#endif //DAY_05_H
