#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class PriorityQueue
{
private:
    vector<int> keys;
    void shiftRight(int low, int high);
    void shiftLeft(int low, int high);
public:
    PriorityQueue(){}
    void buildHeap();
    PriorityQueue(vector<int>& items)
    {
        keys = items;
        buildHeap();
    }

    void enqueue(int item);
    void dequeue();
    void print();
};

void PriorityQueue::shiftRight(int low,int high)
{
    int root = low;

    while((root*2)+1 <= high)
        {
            int leftChild = (root*2) + 1;
            int rightChild = (root*2) + 2;
            int swapIndex = root;

            if(keys[swapIndex] < keys[leftChild])
                {
                    swapIndex = leftChild;
                }
            if((rightChild <= high) && (keys[swapIndex] < keys[rightChild]))
                {
                    swapIndex = rightChild;
                }
            if(swapIndex != root)
                {
                    int temp = keys[root];
                    keys[root] = keys[swapIndex];
                    keys[swapIndex] = temp;

                    root = swapIndex;
                }
            else
                {
                    break;
                }

        }
        return ;
}

void PriorityQueue::shiftLeft(int low,int high)
{
    int childIndex = high;

    while(childIndex > low)
        {
            int parentIndex = (childIndex-1)/2;

            if(keys[childIndex] > keys[parentIndex])
                {
                    int temp = keys[childIndex];
                    keys[childIndex] = keys[parentIndex];
                    keys[parentIndex] = temp;

                    childIndex = parentIndex;
                }
            else
                {
                    break;
                }

        }
        return;
}

void PriorityQueue::enqueue(int item)
{

}

