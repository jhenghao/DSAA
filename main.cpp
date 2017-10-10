#include "BinaryHeap.h"

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

    return 0;
}
