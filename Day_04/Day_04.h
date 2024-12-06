//
// Created by rejamoto on 12/6/24.
//

#ifndef DAY_04_H
#define DAY_04_H

#include "../Day_Base.h"

class Day_04 : protected Day_Base
{
public:
    Day_04()
    {
        DataFile = "../Day_04/Data.txt";
        DataTestFile = "../Day_04/Data_Test.txt";
    }
    ~Day_04() = default;

    void Run();

private:
    struct XmasData : std::vector<std::string> {};
    const std::string XMAS = "XMAS";
    const std::string X_MAS = "MMSS";
    std::vector<std::pair<int, int>> Directions
    {
        {-1, -1},
        {1, -1},
        {0, -1},

        {-1, 0},
        {1, 0},
        {0, 0},

        {-1, 1},
        {1, 1},
        {0, 1}
    };
    enum Direction : size_t
    {
        TopLeft,
        TopRight,
        TopCenter,

        CenterLeft,
        CenterRight,
        CenterCenter,

        BottomLeft,
        BottomRight,
        BottomCenter
    };

    void Solution_1(const XmasData& data);
    void Solution_2(const XmasData& data);

    bool ConfirmXmas(int& count, int index, int x, int y, const XmasData& data, Direction direction = CenterCenter);
    bool ConfirmX_Mas(int x, int y, const XmasData& data);

    static XmasData ReadData(const std::string& path);
};

#endif //DAY_04_H
