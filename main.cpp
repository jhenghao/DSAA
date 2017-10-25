#include "BinaryHeap.h"
#include "LongestCommonSubsequence.h"
#include "Utilities.h"

#include <iostream>

int main ()
{
    using namespace DSAA;

    BinaryHeap binaryHeap({7, 3, 3, 5, 8, 1});
    //binaryHeap.Sort();
    //binaryHeap.Print();

    binaryHeap.IncreaseKey(2, 4);
    binaryHeap.Insert(2);
    binaryHeap.Insert(6);

    while (!binaryHeap.IsEmpty())
    {
        std::cout << binaryHeap.ExtractMax() << std::endl;
    }

    std::cout << "############" << std::endl;
    std::cout << Utilities::IsFloatingNumberIntegral(15.0) << std::endl;

    std::cout << "LCS" << std::endl;
    std::string a = "ABCBDAB";
    std::string b = "BDCABA";
    //std::string a = "ABC";
    //std::string b = "CBA";
    std::cout << LongestCommonSubsequence::GetLength(a, b) << std::endl;
    auto ret = LongestCommonSubsequence::GetAllSubsequences(a, b);

    for (auto& str : ret)
    {
        std::cout << str << std::endl;
    }

    return 0;
}
