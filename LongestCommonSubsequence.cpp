#include "LongestCommonSubsequence.h"

#include <functional>
#include <vector>

namespace
{

auto BuildCountTable = [](const std::string& a, const std::string& b)
{
    std::vector<std::vector<size_t>> counts(a.size() + 1,
        std::vector<size_t>(b.size() + 1, 0));

    for (size_t row = 1; row <= a.size(); ++row)
    {
        for (size_t col = 1; col <= b.size(); ++col)
        {
            if (a[row - 1] == b[col - 1])
            {
                counts[row][col] = counts[row - 1][col - 1] + 1;
            }
            else
            {
                counts[row][col] =
                    std::max(counts[row][col - 1], counts[row - 1][col]);
            }
        }
    }

    return counts;
};

}

namespace DSAA
{

namespace LongestCommonSubsequence
{

size_t GetLength(const std::string& a, const std::string& b)
{
    auto countTable = BuildCountTable(a, b);
    return countTable[a.size()][b.size()];
}

std::string GetOneSubsequence(const std::string& a, const std::string& b)
{
    const auto countTable = BuildCountTable(a, b);

    std::function<std::string(size_t, size_t)> Backtrack;

    Backtrack = [&Backtrack, &countTable, &a, &b](size_t row, size_t col)
        -> std::string
    {
        if (0 == row || 0 == col)
            return "";

        if (a[row - 1] == b[col - 1])
        {
            return Backtrack(row - 1, col - 1) + a[row - 1];
        }

        if (countTable[row][col - 1] > countTable[row - 1][col])
        {
            return Backtrack(row, col - 1);
        }

        return Backtrack(row - 1, col);
    };

    return Backtrack(a.size(), b.size());
}

std::set<std::string> GetAllSubsequences(
    const std::string& a, const std::string& b)
{
    const auto countTable = BuildCountTable(a, b);

    std::set<std::string> ret;
    std::function<void(size_t, size_t, const std::string)> Backtrack;

    Backtrack = [&Backtrack, &countTable, &a, &b, &ret](
        size_t row, size_t col, const std::string suffix)
    {
        if (0 == row || 0 == col)
        {
            if (suffix.empty())
                return;

            if (ret.find(suffix) != ret.end())
                return;

            ret.insert(suffix);
            return;
        }

        if (a[row - 1] == b[col - 1])
        {
            Backtrack(row - 1, col - 1, a[row - 1] + suffix);
            return;
        }

        if (countTable[row][col - 1] >= countTable[row - 1][col])
        {
            Backtrack(row, col - 1, suffix);
        }

        if (countTable[row][col - 1] <= countTable[row - 1][col])
        {
            Backtrack(row - 1, col, suffix);
        }
    };

    Backtrack(a.size(), b.size(), "");
    return ret;
}

}

}
