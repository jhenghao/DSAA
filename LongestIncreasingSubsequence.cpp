#include "LongestIncreasingSubsequence.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

namespace
{

// return length of longest increasing subsequence that ends at curIdx
//------------------------------------------------------------------------------
size_t BinarySearch (
    const std::vector<int>& input, std::vector<size_t>& minimalValues,
    size_t minLength, size_t maxLength, const size_t curIdx, const bool strict)
{
    if (minLength == maxLength)
    {
        size_t prevIdx = minimalValues[minLength];
        if (input[curIdx] < input[prevIdx])
            return minLength;

        if (strict && input[curIdx] == input[prevIdx])
            return minLength;

        return minLength + 1;
    }

    size_t mid = (minLength + maxLength) / 2;
    size_t prevIdx = minimalValues[mid];

    // can concatenate current element
    if (input[curIdx] > input[prevIdx])
        return BinarySearch(input, minimalValues, mid + 1, maxLength, curIdx, strict);

    // can concatenate current element
    if (false == strict && input[curIdx] == input[prevIdx])
        return BinarySearch(input, minimalValues, mid + 1, maxLength, curIdx, strict);

    // can not concatenate current element
    maxLength = mid - 1;
    if (maxLength < minLength)
        maxLength = minLength;

    return BinarySearch(input, minimalValues, minLength, maxLength, curIdx, strict);
};

//------------------------------------------------------------------------------
size_t GetLengthN2 (const std::vector<int>& input, bool strict)
{
    const size_t size = input.size();
    if (0 == size)
        return 0;

    // length of longest increaing subsequence that ends at given idx
    std::vector<size_t> lengths(size, 1);
    size_t maxLength = 0;

    for (size_t curIdx = 0; curIdx < size; ++curIdx)
    {
        for (int prevIdx = curIdx - 1; prevIdx >= 0; --prevIdx)
        {
            if (input[curIdx] < input[prevIdx])
                continue;

            if (strict && input[curIdx] == input[prevIdx])
                continue;

            lengths[curIdx] = std::max(lengths[curIdx], lengths[prevIdx] + 1);
        }

        maxLength = std::max(maxLength, lengths[curIdx]);
    }

    return maxLength;
}

//------------------------------------------------------------------------------
size_t GetLengthNLogN (const std::vector<int>& input, bool strict)
{
    const size_t size = input.size();
    if (0 == size)
        return 0;

    // store minimal value (by element idx) among all last elements of longest
    // increaing subsequences of given length
    std::vector<size_t> minimalValues(2, -1);
    minimalValues[1] = 0;

    for (size_t curIdx = 1; curIdx < size; ++curIdx)
    {
        size_t length = BinarySearch(input, minimalValues,
            1, minimalValues.size() - 1, curIdx, strict);

        if (length >= minimalValues.size())
        {
            minimalValues.push_back(curIdx);
            continue;
        }
        
        size_t prevIdx = minimalValues[length];
        if (input[curIdx] < input[prevIdx])
            minimalValues[length] = curIdx;
    }

    return minimalValues.size() - 1;
}

//------------------------------------------------------------------------------
std::vector<int> GetOneSubsequenceN2 (const std::vector<int>& input, bool strict)
{
    const size_t size = input.size();
    if (0 == size)
        return std::vector<int>();

    std::vector<int> parents(size, -1);

    // length of longest increaing subsequence that ends at given idx
    std::vector<size_t> lengths(size, 0);

    for (size_t curIdx = 0; curIdx < size; ++curIdx)
    {
        size_t maxLength = 0;

        for (int prevIdx = curIdx - 1; prevIdx >= 0; --prevIdx)
        {
            if (input[curIdx] < input[prevIdx])
                continue;

            if (strict && input[curIdx] == input[prevIdx])
                continue;

            if (maxLength >= lengths[prevIdx])
                continue;

            maxLength = lengths[prevIdx];
            parents[curIdx] = prevIdx;
        }

        lengths[curIdx] = maxLength + 1;
    }

    // end idx of a longest increasing subsequence
    size_t endIdx = 0;

    for (size_t idx = 1; idx < size; ++idx)
    {
        if (lengths[idx] > lengths[endIdx])
            endIdx = idx;
    }

    std::vector<int> ret;
    while (endIdx != -1)
    {
        ret.push_back(input[endIdx]);
        endIdx = parents[endIdx];
    } 

    std::reverse(ret.begin(), ret.end());
    return ret;
}

//------------------------------------------------------------------------------
std::vector<int> GetOneSubsequenceNLogN(const std::vector<int>& input, bool strict)
{
    const size_t size = input.size();
    if (0 == size)
        return std::vector<int>();

    std::vector<int> parents(size, -1);

    // store minimal value (by element idx) among all last elements of longest
    // increaing subsequences of given length
    std::vector<size_t> minimalValues(2, -1);
    minimalValues[1] = 0;

    for (size_t curIdx = 1; curIdx < size; ++curIdx)
    {
        size_t length = BinarySearch(input, minimalValues, 
            1, minimalValues.size() - 1, curIdx, strict);
        parents[curIdx] = minimalValues[length - 1];

        if (length >= minimalValues.size())
        {
            minimalValues.push_back(curIdx);
            continue;
        }
        
        size_t prevIdx = minimalValues[length];
        if (input[curIdx] < input[prevIdx])
            minimalValues[length] = curIdx;
    }

    // end idx of a longest increasing subsequence
    size_t endIdx = minimalValues.back();

    std::vector<int> ret;
    while (endIdx != -1)
    {
        ret.push_back(input[endIdx]);
        endIdx = parents[endIdx];
    } 

    std::reverse(ret.begin(), ret.end());
    return ret;
}

}

namespace DSAA
{

namespace LongestIncreasingSubsequence
{

//------------------------------------------------------------------------------
size_t GetLength (const std::vector<int>& input, Complexity complexity,
    bool strict)
{
    switch (complexity)
    {
    case Complexity::eN2:
        return GetLengthN2(input, strict);
    case Complexity::eNLogN:
        return GetLengthNLogN(input, strict);
    }

    return 0;
}

//------------------------------------------------------------------------------
std::vector<int> GetOneSubsequence (const std::vector<int>& input,
    Complexity complexity, bool strict)
{
    switch (complexity)
    {
    case Complexity::eN2:
        return GetOneSubsequenceN2(input, strict);
    case Complexity::eNLogN:
        return GetOneSubsequenceNLogN(input, strict);
    }

    return std::vector<int>();
}

//------------------------------------------------------------------------------
void RunTestCases ()
{
    const std::vector<int> input1 =
        {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

    const std::vector<int> input2 =
        {1, 1, 1, 2, 2, 3, 1, 3, 3, 2, 2, 1};

    // test GetLengthN2
    {
        size_t ret = GetLength(input1, Complexity::eN2, false);
        assert(6 == ret);
    }

    // test GetLengthN2 (non-decreasing)
    {
        size_t ret = GetLength(input2, Complexity::eN2, false);
        assert(8 == ret);
    }

    // test GetLengthN2 (strictly increasing)
    {
        size_t ret = GetLength(input2, Complexity::eN2, true);
        assert(3 == ret);
    }

    // test GetLengthNLogN
    {
        size_t ret = GetLength(input1, Complexity::eNLogN, false);
        assert(6 == ret);
    }

    // test GetLengthNLogN (non-decreasing)
    {
        size_t ret = GetLength(input2, Complexity::eNLogN, false);
        assert(8 == ret);
    }

    // test GetLengthNLogN (strictly increasing)
    {
        size_t ret = GetLength(input2, Complexity::eNLogN, true);
        assert(3 == ret);
    }

    // test GetOneSubsequenceN2
    {
        std::vector<int> ret = GetOneSubsequence(input1, Complexity::eN2, false);
        assert(6 == ret.size());
        assert(std::is_sorted(ret.begin(), ret.end()));
    }

    // test GetOneSubsequenceN2 (non-decreasing)
    {
        std::vector<int> ret = GetOneSubsequence(input2, Complexity::eN2, false);
        assert(8 == ret.size());
        assert(std::is_sorted(ret.begin(), ret.end()));
    }

    // test GetOneSubsequenceN2 (strictly increasing)
    {
        std::vector<int> ret = GetOneSubsequence(input2, Complexity::eN2, true);
        assert(3 == ret.size());
        assert(std::is_sorted(ret.begin(), ret.end()));
    }

    // test GetOneSubsequenceNLogN
    {
        std::vector<int> ret = GetOneSubsequence(input1, Complexity::eNLogN, false);
        assert(6 == ret.size());
        assert(std::is_sorted(ret.begin(), ret.end()));
    }

    // test GetOneSubsequenceNLogN (non-decreasing)
    {
        std::vector<int> ret = GetOneSubsequence(input2, Complexity::eNLogN, false);
        assert(8 == ret.size());
        assert(std::is_sorted(ret.begin(), ret.end()));
    }

    // test GetOneSubsequenceNLogN (strictly increasing)
    {
        std::vector<int> ret = GetOneSubsequence(input2, Complexity::eNLogN, true);
        assert(3 == ret.size());
        assert(std::is_sorted(ret.begin(), ret.end()));
    }
}

}

}
