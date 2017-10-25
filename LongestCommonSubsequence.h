#ifndef DSAA_LONGESTCOMMONSUBSEQUENCE_H
#define DSAA_LONGESTCOMMONSUBSEQUENCE_H

#include <set>
#include <string>

namespace DSAA
{

namespace LongestCommonSubsequence
{

size_t GetLength(const std::string& a, const std::string& b);

std::string GetOneSubsequence(const std::string& a, const std::string& b);

std::set<std::string> GetAllSubsequences(
    const std::string& a, const std::string& b);

}

}

#endif
