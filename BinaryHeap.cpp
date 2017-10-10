#include "BinaryHeap.h"

#include <iostream>

namespace
{

//------------------------------------------------------------------------------
inline size_t GetParentIdx (size_t idx)
{
    return (idx - 1) >> 1;
}

//------------------------------------------------------------------------------
inline size_t GetLeftChildIdx (size_t idx)
{
    return (idx << 1) + 1;
}

//------------------------------------------------------------------------------
inline size_t GetRightChildIdx (size_t idx)
{
    return (idx + 1) << 1;
}

}

namespace DSAA
{

//------------------------------------------------------------------------------
BinaryHeap::BinaryHeap (const std::vector<int>& input)
    : m_Heap(input)
{
    BuildMaxHeap();
}

//------------------------------------------------------------------------------
void BinaryHeap::Print ()
{
    for (const auto& number : m_Heap)
        std::cout << number << ",";

    std::cout << std::endl;
}

//------------------------------------------------------------------------------
void BinaryHeap::Sort ()
{
    size_t heapSize = m_Heap.size();
    if (!heapSize)
        return;

    for (size_t idx = heapSize - 1; idx > 0; --idx)
    {
        std::swap(m_Heap[0], m_Heap[idx]);
        --heapSize;
        MaxHeapify(0, heapSize);
    }

    // keep decreasing order to maintain max heap
    std::reverse(m_Heap.begin(), m_Heap.end());
}

//------------------------------------------------------------------------------
int BinaryHeap::Maximum()
{
    if (m_Heap.empty())
        return INT_MIN;

    return m_Heap[0];
}

//------------------------------------------------------------------------------
int BinaryHeap::ExtractMax()
{
    if (m_Heap.empty())
        return INT_MIN;

    int ret = m_Heap[0];

    m_Heap[0] = m_Heap.back();
    m_Heap.pop_back();
    MaxHeapify(0, m_Heap.size());

    return ret;
}

//------------------------------------------------------------------------------
bool BinaryHeap::IncreaseKey(size_t idx, int number)
{
    const size_t heapSize = m_Heap.size();
    if (idx >= heapSize)
        return false;

    if (number <= m_Heap[idx])
        return false;

    m_Heap[idx] = number;

    while (idx > 0 && m_Heap[GetParentIdx(idx)] < m_Heap[idx])
    {
        size_t parentIdx = GetParentIdx(idx);
        std::swap(m_Heap[idx], m_Heap[parentIdx]);
        idx = parentIdx;
    }

    return true;
}

//------------------------------------------------------------------------------
void BinaryHeap::Insert(int number)
{
    m_Heap.push_back(INT_MIN);
    IncreaseKey(m_Heap.size() - 1, number);
}

//------------------------------------------------------------------------------
void BinaryHeap::BuildMaxHeap ()
{
    const size_t heapSize = m_Heap.size();
    if (!heapSize)
        return;

    for (int idx = m_Heap.size() / 2; idx >= 0; --idx)
    {
        MaxHeapify(idx, heapSize);
    }
}

//------------------------------------------------------------------------------
void BinaryHeap::MaxHeapify (const size_t idx, const size_t heapSize)
{
    if (idx >= heapSize)
        return;

    int leftChildIdx = GetLeftChildIdx(idx);
    int leftChild = INT_MIN;
    if (leftChildIdx < heapSize)
        leftChild = m_Heap[leftChildIdx];

    int rightChildIdx = GetRightChildIdx(idx);
    int rightChild = INT_MIN;
    if (rightChildIdx < heapSize)
        rightChild = m_Heap[rightChildIdx];

    if (m_Heap[idx] >= leftChild && m_Heap[idx] >= rightChild)
        return;

    if (leftChild > rightChild && leftChildIdx < heapSize)
    {
        std::swap(m_Heap[idx], m_Heap[leftChildIdx]);
        MaxHeapify(leftChildIdx, heapSize);
    }
    else
    {
        std::swap(m_Heap[idx], m_Heap[rightChildIdx]);
        MaxHeapify(rightChildIdx, heapSize);
    }
}

}
