//
// Created by rejamoto on 12/3/24.
//

#include "Day_03.h"

void Day_03::Run() const
{
    std::vector<std::tuple<int, int, bool>> data = ReadData(DataFile);
    //std::vector<std::tuple<int, int, bool>> data = ReadData(DataTestFile);

    Solution_1(data);
    Solution_2(data);
}

void Day_03::Solution_1(std::vector<std::tuple<int, int, bool>> &data)
{
    int total = 0;

    for (auto  mul : data)
    {
        total += std::get<0>(mul) * std::get<1>(mul);
    }

    std::cout << "Solution_1: " << total << std::endl;
}

void Day_03::Solution_2(std::vector<std::tuple<int, int, bool>> &data)
{
    int total = 0;

    for (auto & mul : data)
    {
        if (!std::get<2>(mul)) continue;

        total += std::get<0>(mul) * std::get<1>(mul);
    }

    std::cout << "Solution_1: " << total << std::endl;
}

std::vector<std::tuple<int, int, bool>> Day_03::ReadData(const std::string &path)
{
    std::vector<std::tuple<int, int, bool>> data;
    std::ifstream dataFile(path);

    if (!dataFile.is_open())
    {
        Console_WL("File could not be opened");

        return data;
    }

    std::string lineStr;
    bool used = true;

    while (std::getline(dataFile, lineStr))
    {
        if (lineStr.empty()) continue;

        do
        {
            // Find "(" character
            size_t leftParenthesisIndex = lineStr.find('(');

            if (leftParenthesisIndex == std::string::npos) break;

            // Find ")" character
            size_t rightParenthesisIndex = lineStr.find(')', leftParenthesisIndex);

            if (rightParenthesisIndex == std::string::npos) break;

            // Check for "do()" or "don't()"
            if (leftParenthesisIndex + 1 == rightParenthesisIndex)
            {
                // "do()"
                if (leftParenthesisIndex >= 2 &&
                    lineStr.substr(leftParenthesisIndex - 2, 2) == "do")
                { used = true; }

                // "don't()"
                if (leftParenthesisIndex >= 5 &&
                    lineStr.substr(leftParenthesisIndex - 5, 5) == "don't")
                { used = false; }

                lineStr = lineStr.substr(leftParenthesisIndex + 1);
                continue;
            }

            // Invalid section if "mul" not found before "("
            if (leftParenthesisIndex < 3 ||
                lineStr.substr(leftParenthesisIndex - 3, 3) != "mul")
            {
                lineStr = lineStr.substr(leftParenthesisIndex + 1);
                continue;
            }

            // Pull out string between parentheses
            std::string mulStr = lineStr.substr(leftParenthesisIndex + 1, rightParenthesisIndex - leftParenthesisIndex - 1);

            lineStr = lineStr.substr(leftParenthesisIndex + 1);

            // Find "," character
            size_t commaIndex = mulStr.find(',');

            // Separate left and right string
            std::string leftNumStr = mulStr.substr(0, commaIndex);
            std::string rightNumStr = mulStr.substr(commaIndex + 1);

            // Invalid section if contain spaces or either strings are not numbers
            if (mulStr.contains(' ') ||
                !std::all_of(leftNumStr.begin(), leftNumStr.end(), isdigit) ||
                !std::all_of(rightNumStr.begin(), rightNumStr.end(), isdigit))
            { continue; }

            // Insert section
            data.emplace_back(std::stoi(leftNumStr), std::stoi(rightNumStr), used);
        } while (!lineStr.empty());
    }

    return data;
}
