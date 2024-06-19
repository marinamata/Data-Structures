// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void MergeSort(std::vector<int>* numbers, int& countCompare, int& countMemory);
void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int& countCompare, int& countMemory);
void Merge(std::vector<int>* numbers, int i, int j, int k, int& countCompare, int& countMemory);
