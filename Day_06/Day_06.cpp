//
// Created by rejamoto on 12/15/24.
//

#include "Day_06.h"

void Day_06::Run()
{
    LevelData data = ReadData(DataFile);
    //LevelData data = ReadData(DataTestFile);

    Solution_1(data);

    data.ResetLevel();

    Solution_2(data);
}

void Day_06::Solution_1(LevelData data)
{
    do
    {
        data.GuardData.TakeStep();
    } while (data.GuardData.IsOnMap());

    size_t visitedNodes = 0;

    for (const auto& row : data.FloorNodes)
        for (const auto& col : row)
            if (col->Explored) ++visitedNodes;

    PrintLevel(data);

    std::cout << "Solution_1: " << visitedNodes << std::endl;
}

void Day_06::Solution_2(LevelData data)
{
    PrintLevel(data);
}

Day_06::LevelData Day_06::ReadData(const std::string& path)
{
    LevelData data;
    std::ifstream dataFile(path);

    if (!dataFile.is_open())
    {
        Console_WL("File could not be opened");

        return data;
    }

    std::string lineStr;
    std::vector<std::shared_ptr<FloorNode>> previousRow;

    while (std::getline(dataFile, lineStr))
    {
        if (lineStr.empty()) continue;

        std::vector<std::shared_ptr<FloorNode>> currentRow;

        for (size_t i = 0; i < lineStr.size(); i++)
        {
            const char c    = lineStr[i];
            auto *node = new FloorNode();

            if (c == '.')
            {
                node->Contains = Empty;
            }
            else if (c == '#')
            {
                node->Contains = Object;
            }
            else
            {
                node->Contains = Human;
                node->Explored = true;

                // Guard found
                Guard guard;
                guard.CurrentNode = node;
                guard.OriginalNode = node;

                if (c == '^')
                    guard.CurrentDirection = N;
                else if (c == 'v')
                    guard.CurrentDirection = S;
                else if (c == '<')
                    guard.CurrentDirection = W;
                else if (c == '>')
                    guard.CurrentDirection = E;

                guard.OriginalDirection = guard.CurrentDirection;

                data.GuardData = guard;
            }

            // Connect to W node
            if (!currentRow.empty())
            {
                node->NearbyNodes[W] = currentRow[i - 1].get();
                currentRow[i - 1]->NearbyNodes[E] = node;
            }

            currentRow.emplace_back(node);

            if (previousRow.empty()) continue;

            // Connect to NW
            if (i > 0)
            {
                node->NearbyNodes[NW] = previousRow[i - 1].get();
                previousRow[i - 1]->NearbyNodes[SE] = node;
            }

            // Connect to N
            node->NearbyNodes[N] = previousRow[i].get();
            previousRow[i]->NearbyNodes[S] = node;

            // Connect to NE
            if (previousRow.size() - 1 == i) continue;

            node->NearbyNodes[NE] = previousRow[i + 1].get();
            previousRow[i + 1]->NearbyNodes[SW] = node;
        }

        data.FloorNodes.emplace_back(currentRow);
        previousRow = currentRow;
    }

    return data;
}

void Day_06::PrintLevel(const LevelData& data)
{
    for (const auto& row : data.FloorNodes)
    {
        for (const auto& col : row)
        {
            if (col->Explored)
                std::cout << 'X';
            else if (col->Contains == Object)
                std::cout << '#';
            else
                std::cout << '.';
        }

        std::cout << std::endl;
    }
}

void Day_06::LevelData::ResetLevel()
{
    for (auto& row : FloorNodes)
    {
        for (const auto& col : row)
        {
            col->Explored = false;

            if (col->Contains == Human)
                col->Contains = Empty;
        }
    }

    GuardData.CurrentDirection = GuardData.OriginalDirection;
    GuardData.CurrentNode = GuardData.OriginalNode;
    GuardData.CurrentNode->Explored = true;
    GuardData.CurrentNode->Contains = Human;
}

void Day_06::Guard::TakeStep()
{
    // Already left
    if (CurrentNode == nullptr) return;

    // Check next node
    FloorNode* nextNode;
    bool validMove = false;

    do
    {
        nextNode = CurrentNode->NearbyNodes[CurrentDirection];

        if (nextNode == nullptr) break;

        // Change direction if next node has object
        if (nextNode->Contains == Object)
        {
            if (CurrentDirection == N)
                CurrentDirection = E;
            else if (CurrentDirection == E)
                CurrentDirection = S;
            else if (CurrentDirection == S)
                CurrentDirection = W;
            else if (CurrentDirection == W)
                CurrentDirection = N;

            continue;
        }

        validMove = true;
    } while (!validMove);

    CurrentNode->Contains = Empty;

    // If null, guard has left the map
    if (nextNode == nullptr)
    {
        CurrentNode = nullptr;
    }
    else
    {
        nextNode->Contains = Human;
        nextNode->Explored = true;
        CurrentNode = nextNode;
    }
}
