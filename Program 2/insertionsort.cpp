// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks
#include <iostream>
#include "insertionsort.h"
using namespace std;
void InsertionSort(std::vector<int>* numbers,int& insertion_compareCount, int& insertion_numberOfMemoryAccesses ) {
   int i = 0;
   int j = 0;
   int temp = 0;  // Temporary variable for swap


   for (i = 1; i < numbers->size(); ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
         insertion_numberOfMemoryAccesses +=2;
         insertion_compareCount  +=1;
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
          insertion_numberOfMemoryAccesses +=1;
         (*numbers)[j] = (*numbers)[j - 1];
          insertion_numberOfMemoryAccesses +=2;
         (*numbers)[j - 1] = temp;
         insertion_numberOfMemoryAccesses +=1;
         --j;
      }

      if(j > 0){  // If j is 0, then the while loop was never entered
         insertion_numberOfMemoryAccesses +=2;
         insertion_compareCount += 1;
      }
   }
   
   return;
}

