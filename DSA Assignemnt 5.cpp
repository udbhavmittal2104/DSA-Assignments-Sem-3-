#include <bits/stdc++.h>
using namespace std;
int arr[1000];
static int s = 0;
void insertMinHeap(int val)
{
    s++;
    int index = s;
    arr[index] = val;

    while (index > 1)
    {
        int parent = index / 2;

        if (arr[parent] > arr[index])
        {
            swap(arr[parent], arr[index]);
            index = parent;
        }
        else
            return;
    }
}
void deleteHeap(int size)
{
    if (size == 0)
    {
        printf("Nothing to delete\n");
        return;
    }
    arr[1] = arr[size];
    size--;
    int i = 1;
    while (i < size)
    {
        int leftInd = 2 * i;
        int rightInd = 2 * i + 1;
        if (leftInd <= size && arr[i] > arr[leftInd] && arr[leftInd] < arr[rightInd])
        {
            swap(arr[i], arr[leftInd]);
            i = leftInd;
        }
        else if (rightInd <= size && arr[i] > arr[rightInd] && arr[rightInd] < arr[leftInd])
        {
            swap(arr[i], arr[rightInd]);
            i = rightInd;
        }
        else
            return;
    }
}
void print(int size)
{
    for (int i = 1; i <= size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main()
{
    int size;
    printf("Enter the size: ");
    scanf("%d", &size);
    printf("Enter the numbers: ");
    for (int i = 0; i < size; i++)
    {
        int val;
        scanf("%d", &val);
        insertMinHeap(val);
    }
    print(size);
    deleteHeap(size);
    print(size=size-1);
    deleteHeap(size);
    print(size=size-1);
}