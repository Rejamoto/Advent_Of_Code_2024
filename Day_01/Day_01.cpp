//
// Created by rejamoto on 12/2/24.
//

#include "Day_01.h"

void Day_01::Run()
{
    std::pair<std::vector<int>, std::vector<int>> data = ReadData(DataFile);
    //std::pair<std::vector<int>, std::vector<int>> data = ReadData(DataTestFile);

    Solution_1(data);
    Solution_2(data);
}

void Day_01::Solution_1(std::pair<std::vector<int>, std::vector<int>>& data)
{
    // Sort both vectors ascending order
    std::sort(data.first.begin(), data.first.end());
    std::sort(data.second.begin(), data.second.end());

    int totalDistance = 0;

    for (int i = 0; i < data.first.size(); i++)
    {
        totalDistance += std::abs(data.first[i] - data.second[i]);
    }

    std::cout << "Solution_1: " << totalDistance << std::endl;
}

void Day_01::Solution_2(std::pair<std::vector<int>, std::vector<int>>& data)
{
    int totalSimilarityScore = 0;

    for (const int left : data.first)
    {
        int score = 0;

        for (const int right : data.second)
        {
            if (left == right) score += left;
        }

        totalSimilarityScore += score;
    }

    std::cout << "Solution_2: " << totalSimilarityScore << std::endl;
}

std::pair<std::vector<int>, std::vector<int>> Day_01::ReadData(const std::string& path)
{
    std::pair<std::vector<int>, std::vector<int>> data;
    std::ifstream dataFile(path);

    if (!dataFile.is_open())
    {
        Console_WL("File could not be opened");

        return data;
    }

    std::string lineStr;

    while (std::getline(dataFile, lineStr))
    {
        if (lineStr.empty()) { continue; }

        // First number
        size_t spaceIndex       = lineStr.find_first_of(' ');
        data.first.emplace_back(stoi(lineStr.substr(0, spaceIndex)));

        // Second number
        data.second.emplace_back(stoi(TrimString(lineStr.substr(spaceIndex + 1))));
    }

    return data;
}

std::string Day_01::TrimString(const std::string &str, const std::string& whitespace)
{
    const size_t strBeginIndex = str.find_first_not_of(whitespace);

    if (strBeginIndex == std::string::npos) return "";

    const size_t strEndIndex = str.find_last_not_of(whitespace);
    const size_t strRange = strEndIndex - strBeginIndex + 1;

    return str.substr(strBeginIndex, strRange);
}