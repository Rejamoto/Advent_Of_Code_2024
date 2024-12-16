//
// Created by rejamoto on 12/15/24.
//

#ifndef DAY_06_H
#define DAY_06_H

#include <memory>

#include "../Day_Base.h"

class Day_06 : protected Day_Base
{
public:
    Day_06()
    {
        DataFile = "../Day_06/Data.txt";
        DataTestFile = "../Day_06/Data_Test.txt";
    }
    ~Day_06() = default;

    void Run();

    enum FloorObject
    {
        Empty,
        Human,
        Object
    };
    enum Direction
    {
        NW,  N, NE,
         W,      E,
        SW,  S, SE
    };

    class FloorNode
    {
    public:
        FloorNode() = default;
        ~FloorNode() = default;

        std::vector<FloorNode*> NearbyNodes {8};
        FloorObject Contains = Empty;
        bool Explored = false;
    };

    class Guard
    {
    public:
        Guard() = default;
        Guard(FloorNode* floor_node, const Direction direction)
        {
            CurrentNode = floor_node;
            CurrentDirection = direction;
        }
        ~Guard() = default;

        FloorNode *CurrentNode = nullptr;
        Direction CurrentDirection   = NW;

        FloorNode *OriginalNode = nullptr;
        Direction OriginalDirection = NW;

        void TakeStep();
        [[nodiscard]] bool IsOnMap() const { return CurrentNode != nullptr; }
    };

    struct LevelData
    {
        std::vector<std::vector<std::shared_ptr<FloorNode>>> FloorNodes;
        Guard GuardData;

        void ResetLevel();
    };

private:
    static void Solution_1(LevelData data);
    void Solution_2(LevelData data);

    static LevelData ReadData(const std::string& path);

    static void PrintLevel(const LevelData& data);
};

#endif //DAY_06_H
