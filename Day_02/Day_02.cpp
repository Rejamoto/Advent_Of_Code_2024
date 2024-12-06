//
// Created by rejamoto on 12/2/24.
//

#include "Day_02.h"

void Day_02::Run() const
{
    std::vector<std::vector<int>> data = ReadData(DataFile);
    //std::vector<std::vector<int>> data = ReadData(DataTestFile);

    Solution_1(data);
    Solution_2(data);
}

void Day_02::Solution_1(std::vector<std::vector<int> > &data) const
{
    int numReportsSafe = 0;

    for (const std::vector<int> & reportNumbers : data)
    {
        if (CheckReport(reportNumbers)) numReportsSafe++;
    }

    std::cout << "Solution_1: " << numReportsSafe << std::endl;
}

void Day_02::Solution_2(std::vector<std::vector<int> > &data) const
{
    int numReportsSafe = 0;

    for (const std::vector<int> & reportNumbers: data)
    {
        bool safe = CheckReport(reportNumbers);

        for (int i = 0; !safe && i < reportNumbers.size(); i++)
        {
            safe = CheckReport(reportNumbers, i);
        }

        if (safe) numReportsSafe++;
    }

    std::cout << "Solution_2: " << numReportsSafe << std::endl;
}

bool Day_02::CheckReport(const std::vector<int> &reportNumbers, const int &indexSkip) const
{
    // Obtain first number
    int currentNumber = reportNumbers[0];
    bool decreasing = false;
    bool increasing = false;

    bool safe = true;
    int i = 1;

    if (indexSkip == 0)
    {
        currentNumber = reportNumbers[i];
        i++;
    }

    for (; i < reportNumbers.size(); i++)
    {
        if (indexSkip == i) continue;

        int delta = currentNumber - reportNumbers[i];

        // Check if values are changing, at the correct direction, and within tolerance.
        if (delta > 0 && decreasing ||
            delta < 0 && increasing ||
            delta == 0 ||
            std::abs(delta) > Tolerances.second)
        {
            safe = false;
            break;
        }

        if (delta > 0)
            increasing = true;
        else
            decreasing = true;

        // Safe at this point. Retain number.
        currentNumber = reportNumbers[i];
    }

    return safe;
}

std::vector<std::vector<int> > Day_02::ReadData(const std::string &path)
{
    std::vector<std::vector<int>> data;
    std::ifstream dataFile(path);

    if (!dataFile.is_open())
    {
        Console_WL("File could not be opened");

        return data;
    }

    std::string lineStr;

    while (std::getline(dataFile, lineStr))
    {
        if (lineStr.empty()) continue;

        std::vector<int> reportNumbers;

        do
        {
            // Obtain left number
            size_t spaceIndex = lineStr.find(' ');
            std::string numberStr;

            if (spaceIndex > 0 && spaceIndex != std::string::npos)
            {
                numberStr = lineStr.substr(0, spaceIndex);
                lineStr = TrimString(lineStr.substr(spaceIndex + 1));
            }
            else
            {
                numberStr = TrimString(lineStr);
                lineStr = "";
            }

            reportNumbers.emplace_back(std::stoi(numberStr));
        } while (!lineStr.empty());

        data.emplace_back(reportNumbers);
    }

    return data;
}

std::string Day_02::TrimString(const std::string &str, const std::string& whitespace)
{
    const size_t strBeginIndex = str.find_first_not_of(whitespace);

    if (strBeginIndex == std::string::npos) return "";

    const size_t strEndIndex = str.find_last_not_of(whitespace);
    const size_t strRange = strEndIndex - strBeginIndex + 1;

    return str.substr(strBeginIndex, strRange);
}