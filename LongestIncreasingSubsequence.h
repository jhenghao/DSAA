#ifndef DSAA_LONGESTINCREASINGSUBSEQUENCE_H
#define DSAA_LONGESTINCREASINGSUBSEQUENCE_H

#include <vector>

namespace DSAA
{

namespace LongestIncreasingSubsequence
{

enum class Complexity
{
    eN2,
    eNLogN,
};

// @params
//      strict: set true if subsequence should be strictly increasing
size_t GetLength(const std::vector<int>& input, Complexity complexity,
    bool strict);

// @params
//      strict: set true if subsequence should be strictly increasing
std::vector<int> GetOneSubsequence(const std::vector<int>& input, 
    Complexity complexity, bool strict);

void RunTestCases ();

}

}

#endif
