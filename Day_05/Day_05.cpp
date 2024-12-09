//
// Created by rejamoto on 12/8/24.
//

#include "Day_05.h"

#include <cmath>
#include <list>
#include <queue>
#include <bits/ranges_algo.h>

void Day_05::Run() const
{
    SafetyManual data = ReadData(DataFile);
    //SafetyManual data = ReadData(DataTestFile);

    Solution_1(data);
    Solution_2(data);
}

void Day_05::Solution_1(SafetyManual &SafetyManual)
{
    int total = 0;

    for (const auto& printPages: SafetyManual.PagesToPrint)
    {
        std::map<int, bool> printedPages;
        bool printed = true;

        for (const auto print_page: printPages)
        {
            for (const auto&[fst, snd]: SafetyManual.PageOrderRules)
            {
                if (fst != print_page) continue;

                if (printedPages[snd])
                {
                    printed = false;
                    break;
                }
            }

            if (!printed) break;

            printedPages[print_page] = true;
        }

        if (printed) total += printPages[std::floor(printPages.size() / 2)];
        else SafetyManual.IncorrectUpdates.push_back(printPages);
    }

    std::cout << "Solution_1: " << total << std::endl;
}

void Day_05::Solution_2(SafetyManual& SafetyManual)
{
    int total = 0;

    for (const auto& incorrectUpdate : SafetyManual.IncorrectUpdates)
    {
        std::list<int> queue;
        std::ranges::for_each(incorrectUpdate, [&queue](auto q) { queue.push_back(q); });

        std::list<int> correctedUpdate;

        while (!queue.empty())
        {
            int current = queue.front();
            queue.pop_front();

            correctedUpdate.emplace_back(current);

            bool invalid = false;
            bool found = false;
            std::map<int, bool> printedPages;

            for (const int& printPage : correctedUpdate)
            {
                for (const auto&[fst, snd] : SafetyManual.PageOrderRules)
                {
                    if (fst != printPage) continue;

                    if (current == fst) found = true;

                    if (printedPages[snd])
                    {
                        invalid = true;
                        break;
                    }
                }

                if (invalid) break;

                printedPages[printPage] = true;
            }

            if (invalid)
            {
                int num2 = correctedUpdate.back();
                correctedUpdate.pop_back();

                int num1 = correctedUpdate.back();
                correctedUpdate.pop_back();

                correctedUpdate.emplace_back(num2);
                queue.push_front(num1);
            }
            if (!found && !queue.empty())
            {
                int num1 = correctedUpdate.back();
                correctedUpdate.pop_back();

                queue.push_back(num1);
            }
        }

        std::vector temp(correctedUpdate.begin(), correctedUpdate.end());
        total += temp[std::floor(temp.size() / 2)];
    }

    std::cout << "Solution_2: " << total << std::endl;
}

Day_05::SafetyManual Day_05::ReadData(const std::string &path)
{
    SafetyManual data;
    std::ifstream dataFile(path);

    if (!dataFile.is_open())
    {
        Console_WL("File could not be opened");

        return data;
    }

    std::string lineStr;
    bool readingPagesToPrint = false;

    while (std::getline(dataFile, lineStr))
    {
        if (lineStr.empty())
        {
            readingPagesToPrint = true;
            continue;
        }

        if (readingPagesToPrint)
        {
            std::vector<int> pages;

            do
            {
                if (size_t commaIndex = lineStr.find(','); commaIndex == std::string::npos)
                {
                    pages.emplace_back(std::stoi(lineStr));
                    lineStr.clear();
                }
                else
                {
                    pages.emplace_back(std::stoi(lineStr.substr(0, commaIndex)));
                    lineStr = lineStr.substr(commaIndex + 1);
                }
            } while (!lineStr.empty());

            data.PagesToPrint.emplace_back(pages);
        }
        else
        {
            size_t pipeIndex = lineStr.find('|');

            int firstNum = std::stoi(lineStr.substr(0, pipeIndex));
            int secondNum = std::stoi(lineStr.substr(pipeIndex + 1));

            data.PageOrderRules.emplace_back(firstNum, secondNum);
        }
    }

    return data;
}
