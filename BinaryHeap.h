#ifndef DSAA_BINARYHEAP_H
#define DSAA_BINARYHEAP_H

#include <vector>

namespace DSAA
{

// max heap
class BinaryHeap
{
public:
    BinaryHeap (const std::vector<int>& input);

    // print all elements
    void Print();

    // heapsort
    void Sort ();

    // priority queue
    inline bool IsEmpty() { return m_Heap.empty(); }
    int Maximum();
    int ExtractMax();
    bool IncreaseKey(size_t idx, int number);
    void Insert(int number);

private:
    void BuildMaxHeap ();
    void MaxHeapify (const size_t idx, const size_t heapSize);

private:
    std::vector<int> m_Heap;
};

}

#endif
