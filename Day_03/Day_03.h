//
// Created by rejamoto on 12/3/24.
//

#ifndef DAY_03_H
#define DAY_03_H

#include "../Day_Base.h"

class Day_03 : protected Day_Base
{
public:
    Day_03()
    {
        DataFile = "../Day_03/Data.txt";
        DataTestFile = "../Day_03/Data_Test.txt";
    }
    ~Day_03() = default;

    void Run() const;

private:
    static void Solution_1(std::vector<std::tuple<int, int, bool>> &data);
    static void Solution_2(std::vector<std::tuple<int, int, bool>> &data);

    static std::vector<std::tuple<int, int, bool>> ReadData(const std::string& path);
};

#endif //DAY_03_H
