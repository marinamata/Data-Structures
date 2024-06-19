// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<int>* numbers, int& quick_compareCount, int& quick_numberOfMemoryAccesses); //I added dd the parameter 'quick_compareCount' and 'quick_numberOfMemoryAccesses'
void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int& quick_compareCount, int& quick_numberOfMemoryAccesses); //I added the parameter 'quick_compareCount' and 'quick_numberOfMemoryAccesses'
int Partition(std::vector<int>* numbers, int i, int k,  int& quick_compareCount, int& quick_numberOfMemoryAccesses);   //I added the parameters 'quick_compareCount' and 'quick_numberOfMemoryAccesses'

