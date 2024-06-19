//Naveed Sekender 
#include <iostream>
#include <fstream>
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"
#include <ctime>
#include "json.hpp"
#include <chrono>


using namespace std;

void counterInsertion(vector<int>*numbers, double& insertion_count_time, int& insertion_compareCount, int& insertion_numberOfMemoryAccesses); //create count insertion
void counterMerge(vector<int>*numbers, double& merge_count_time, int& Merge_compareCount, int& Merge_numberOfMemoryAccesses); //create count merge
void counterQuick(vector<int>*numbers, double& quick_count_time, int& quick_compareCount, int& quick_numberOfMemoryAccesses); //create count quick 


//declare the timer
    chrono::high_resolution_clock::time_point start;

void counterInsertion(vector<int>*numbers, double& insertion_count_time, int& insertion_compareCount, int& insertion_numberOfMemoryAccesses){//function to record comparisons, time and memory acessed for Insertion sort
    start = chrono::high_resolution_clock::now(); //start the timer for the stuff
    InsertionSort(numbers, insertion_compareCount, insertion_numberOfMemoryAccesses); //call insertion sort, 1 argument(tuple to be sorted)
    auto end = chrono::high_resolution_clock::now(); //end the timer
    insertion_count_time = chrono::duration<double, micro>(end - start).count(); //calculate the difference between the start and end

}

void counterMerge(vector<int>*numbers, double& merge_count_time, int& Merge_compareCount, int& Merge_numberOfMemoryAccesses){   //function to record comparisons, time and memory acessed for Merge sort
    //start the timer 
    start = chrono::high_resolution_clock::now();
    MergeSort(numbers, Merge_compareCount, Merge_numberOfMemoryAccesses); //call merge sort,tuple to be sorted
    auto end = chrono::high_resolution_clock::now(); //end the timer
    merge_count_time = chrono::duration<double, micro>(end - start).count(); //calculate the difference between the start and end
}


void counterQuick(vector<int>*numbers, double& quick_count_time, int& quick_compareCount, int& quick_numberOfMemoryAccesses){    //function to record comparisons, time and memory acessed for  Quick sort
    start = chrono::high_resolution_clock::now(); 
    QuickSort(numbers, quick_compareCount, quick_numberOfMemoryAccesses); //call quick sort, 1 argument(tuple to be sorted)
    auto end = chrono::high_resolution_clock::now(); //end the timer
    quick_count_time = chrono::duration<double, micro>(end - start).count(); //calculate the difference between the start and end
}

// panik
int main(int argc, char** argv) {
    vector<int> numbers; //intialize the vector of number 1
    vector<int> numbers2; //intialize the vector of number 2
    vector<int> numbers3; //intialize the vector of number 3

    std::ifstream json_file(argv[1]); //argv1 into the object
    if (!json_file.is_open()) { //if it cant open 
        std::cerr << "Error: unable to open file " << argv[1] << std::endl; //explain that you can't continue
        return 1;   //return 1
    }
    //open and create object
    nlohmann::json firstJasonObj;     //we are ysubg the nlohmann library
    nlohmann::json outputObject;  //creating the object that prints out the results
    nlohmann::json test;    //creating the object that prints out the results
    json_file >> test;  //reading the json file

//create CSVOuput file;
ofstream csvFile; //this is the output csv file
csvFile.open("output.csv"); //open the output file

//Lines`
csvFile << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTtime,QuickSortCompares,QuickSortMemaccess" << endl; //write the column headers
cout<<"Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTtime,QuickSortCompares,QuickSortMemaccess" << endl; //write the column headers
int i = 0; //initlize a counter variable
for(auto itr = test.begin();itr != test.end();itr++){  //iterate through the entire vector
    if (itr.key() != "metadata") { //as long as its not meta data
    int sampleNumber = i + 1; //add one to the name number eahc time
    if (sampleNumber < 10) { //if its less than 10
        csvFile << "0"; //we will add a zero before it
    }
    csvFile << sampleNumber << ",";
    //this shit is for the inseriton stuff
    double insertion_count_time = 0; //count the time it takes
    int insertion_compareCount = 0; //declare the number of comparisons
    int insertion_numberOfMemoryAccesses = 0; //declare the number of memory accesses


// this shit is for the merge function
    double merge_count_time = 0; //count the time it takes
    int  Merge_compareCount= 0; //declare the number of comparisons
    int Merge_numberOfMemoryAccesses = 0; //declare the number of memory accesses

    //quick check
    double quick_count_time  = 0; //declare the number of comparisons
    int quick_compareCount = 0;  //declare the number of comparisons
    int quick_numberOfMemoryAccesses = 0; //declare the number of memory accesses

    for (auto element: itr.value()) {
        numbers.push_back(element); //pushback stuff into the vector
        numbers2.push_back(element); //pushback stuff into the vector
        numbers3.push_back(element); //pushback stuff into the vector
    }

    counterInsertion(&numbers, insertion_count_time, insertion_compareCount, insertion_numberOfMemoryAccesses); //save the results into a tuple
    csvFile << insertion_count_time << ","<< insertion_compareCount << ","<< insertion_numberOfMemoryAccesses << ','; //add to csv file
    cout << "Sample"; //add the word sample
    if (sampleNumber < 10) { //if the number is less than 10
        cout << "0"; //add a zero before it
    }
    cout << sampleNumber << "," << insertion_count_time << ","<< insertion_compareCount << ","<< insertion_numberOfMemoryAccesses << ','; //print

    counterMerge(&numbers2, merge_count_time, Merge_compareCount, Merge_numberOfMemoryAccesses); //save the results into a tuple
    csvFile << merge_count_time << "," << Merge_compareCount << ","<< Merge_numberOfMemoryAccesses << ','; //save how long it takes to the csv file
    cout << merge_count_time << "," << Merge_compareCount << ","<< Merge_numberOfMemoryAccesses << ','; //show the merge count time

    counterQuick(&numbers3, quick_count_time, quick_compareCount, quick_numberOfMemoryAccesses); //save the results into a tuple
    csvFile << quick_count_time << ","<< quick_compareCount << ","<< quick_numberOfMemoryAccesses << endl; //show the quick count_time
    cout << quick_count_time << ","<< quick_compareCount << ","<< quick_numberOfMemoryAccesses << endl; //show the quick count time

    numbers.erase(numbers.begin(), numbers.end()); //delete the arrays
    numbers2.erase(numbers2.begin(), numbers2.end());  //delete the arrays
    numbers3.erase(numbers3.begin(), numbers3.end());  //delete the arrays
    i++; //add to the I 
}
}
}