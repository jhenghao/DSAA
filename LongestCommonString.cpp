#include "LongestCommonString.h"

#include <algorithm>
#include <iostream>

#include "Utilities.h"

namespace
{

//------------------------------------------------------------------------------
auto BuildCountTable = [](const std::string& a, const std::string& b)
{
    std::vector<std::vector<size_t>> counts(a.size(),
        std::vector<size_t>(b.size(), 0));

    for (size_t row = 0; row < a.size(); ++row)
    {
        for (size_t col = 0; col < b.size(); ++col)
        {
            if (a[row] != b[col])
                continue;

            if (0 == row || 0 == col)
            {
                counts[row][col] = 1;
            }
            else
            {
                counts[row][col] = counts[row - 1][col - 1] + 1;
            }
        }
    }

    return counts;
};

}

namespace DSAA
{

//------------------------------------------------------------------------------
namespace LongestCommonString
{

size_t GetLength (const std::string& a, const std::string& b)
{
    auto countTable = BuildCountTable(a, b);
    size_t maxLength = 0;

    for (size_t row = 0; row < countTable.size(); ++row)
    {
        for (size_t col = 0; col < countTable[0].size(); ++col)
        {
            maxLength = std::max(maxLength, countTable[row][col]);
        }
    }

    return maxLength;
}

//------------------------------------------------------------------------------
std::string GetOneString (const std::string& a, const std::string& b)
{
    const auto countTable = BuildCountTable(a, b);

    size_t maxLength = 0;
    size_t idx = 0;

    for (size_t row = 0; row < countTable.size(); ++row)
    {
        for (size_t col = 0; col < countTable[0].size(); ++col)
        {
            if (maxLength >= countTable[row][col])
                continue;

            maxLength = countTable[row][col];
            idx = row;
        }
    }

    if (0 == maxLength)
        return std::string();

    assert(idx - maxLength + 1 < a.size());
    return a.substr(idx - maxLength + 1, maxLength);
}

//------------------------------------------------------------------------------
std::vector<std::string> GetAllStrings(
    const std::string& a, const std::string& b)
{
    const auto countTable = BuildCountTable(a, b);
    size_t maxLength = 0;

    for (size_t row = 0; row < countTable.size(); ++row)
    {
        for (size_t col = 0; col < countTable[0].size(); ++col)
        {
            maxLength = std::max(maxLength, countTable[row][col]);
        }
    }

    std::vector<std::string> ret;
    if (0 == maxLength)
        return ret;

    for (size_t row = 0; row < countTable.size(); ++row)
    {
        for (size_t col = 0; col < countTable[0].size(); ++col)
        {
            if (maxLength != countTable[row][col])
                continue;

            assert(row - maxLength + 1 < a.size());
            std::string s = a.substr(row - maxLength + 1, maxLength);
            Utilities::AddIfNotExists(ret, s);
        }
    }

    return ret;
}

//------------------------------------------------------------------------------
void RunTestCases ()
{
    {
        std::string m("GeeksforGeeks");
        std::string n("Geeks");

        assert("Geeks" == GetOneString(m, n));
    }

    {
        std::string m("GeeksForRocksForGeeks");
        std::string n("GeeksAndRocks");

        auto ret = GetAllStrings(m, n);
        assert(2 == ret.size());
        assert(Utilities::Exists(ret, "Geeks"));
        assert(Utilities::Exists(ret, "Rocks"));
    }
}

}

}
