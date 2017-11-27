#ifndef DSAA_LONGESTCOMMONSTRING_H
#define DSAA_LONGESTCOMMONSTRING_H

#include <string>
#include <vector>

namespace DSAA
{

namespace LongestCommonString
{

size_t GetLength (const std::string& a, const std::string& b);

std::string GetOneString (const std::string& a, const std::string& b);

std::vector<std::string> GetAllSubsequences(
    const std::string& a, const std::string& b);

void RunTestCases ();

}

}

#endif
