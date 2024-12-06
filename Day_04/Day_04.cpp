//
// Created by rejamoto on 12/6/24.
//

#include "Day_04.h"

void Day_04::Run()
{
    const XmasData data = ReadData(DataFile);
    //const XmasData data = ReadData(DataTestFile);

    Solution_1(data);
    Solution_2(data);
}


void Day_04::Solution_1(const XmasData& data)
{
    int xmasCount = 0;

    for (int y = 0; y < data.size(); y++)
    {
        for (int x = 0; x < data[y].size(); x++)
        {
            if (data[y][x] != 'X') continue;

            ConfirmXmas(xmasCount, 1, x, y, data);
        }
    }

    std::cout << "Solution_1: " << xmasCount << std::endl;
}

void Day_04::Solution_2(const XmasData &data)
{
    int xmasCount = 0;

    for (int y = 1; y < data.size() - 1; y++)
    {
        for (int x = 1; x < data[y].size() - 1; x++)
        {
            if (data[y][x] != 'A') continue;

            if (ConfirmX_Mas(x, y, data)) xmasCount++;
        }
    }

    std::cout << "Solution_2: " << xmasCount << std::endl;
}

bool Day_04::ConfirmXmas(int& count, const int index, const int x, const int y, const XmasData& data, const Direction direction)
{
    if (index >= XMAS.size())
    {
        count++;
        return true;
    }

    const size_t yLimit = data.size();
    const size_t xLimit = data[y].size();

    if (direction == CenterCenter)
    {
        bool found = false;

        for (size_t dir = 0; dir < Directions.size(); dir++)
        {
            const auto dirTemp = static_cast<Direction>(dir);

            if (dirTemp == CenterCenter) continue;

            found |= ConfirmXmas(count, index, x, y, data, dirTemp);
        }

        return found;
    }

    auto [fst, snd] = Directions[direction];
    const int dirX = x + fst;
    const int dirY = y + snd;

    // Check if within boundaries
    if (dirX == xLimit || dirX < 0 ||
        dirY == yLimit || dirY < 0) return false;

    // Check if matches next letter
    if (data[dirY][dirX] != XMAS[index]) return false;

    return ConfirmXmas(count, index + 1, dirX, dirY, data, direction);
}

bool Day_04::ConfirmX_Mas(const int x, const int y, const XmasData &data)
{
    bool m_found = false;
    bool s_found = false;
    std::pair m1_coord(-1, -1);
    std::pair s1_coord(-1, -1);

    for (size_t dir = 0; dir < Directions.size(); dir++)
    {
        const auto dirTemp = static_cast<Direction>(dir);

        if (dirTemp == CenterCenter ||
            dirTemp == TopCenter ||
            dirTemp == BottomCenter ||
            dirTemp == CenterLeft ||
            dirTemp == CenterRight) continue;

        auto [fst, snd] = Directions[dirTemp];
        const int dirX = x + fst;
        const int dirY = y + snd;

        if (data[dirY][dirX] == 'M' && !m_found)
        {
            if (m1_coord.first == -1)
            {
                m1_coord.first = dirX;
                m1_coord.second = dirY;
            }
            else
            {
                m_found = m1_coord.first == dirX || m1_coord.second == dirY;
            }
        }
        if (data[dirY][dirX] == 'S' && !s_found)
        {
            if (s1_coord.first == -1)
            {
                s1_coord.first = dirX;
                s1_coord.second = dirY;
            }
            else
            {
                s_found = s1_coord.first == dirX || s1_coord.second == dirY;
            }
        }
    }

    return m_found && s_found;
}

Day_04::XmasData Day_04::ReadData(const std::string &path)
{
    XmasData data;
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

        do
        {
            data.emplace_back(lineStr);

            lineStr.clear();
        } while (!lineStr.empty());
    }

    return data;
}
