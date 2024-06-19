#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"

PriorityQueue::PriorityQueue(size_t max_size) :                 //Constructor for the PriorityQueue class. 
    max_size_(max_size),                                        //Initializing maximum size of the queue
    size_(0) {                          
    //Changed this line from Professors driver code for debugging            
    nodes_.push_back(std::make_pair(0, std::make_pair(0, 0)));  //one-based indexing 
}

void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));       //Inserts node with key value k
}

void PriorityQueue::insert(KeyValuePair kv) {
    ++size_;                    //Increments size of the queue
    nodes_.push_back(kv);       //pushes new node into kv
    heapifyUp(size_);           //Ensures heap property is maintained
}

KeyValuePair PriorityQueue::min() {
    return nodes_[ROOT];        //returns the minimum node in the priority queue
}

KeyValuePair PriorityQueue::removeMin() {
    auto object = min();            //Declare minimum node
    nodes_[ROOT] = nodes_[size_];   //Check for minimum node
    nodes_.pop_back();              //Removes minimum node from priority queue
    heapifyDown(ROOT);              //Ensures heap property is maintained
    size_--;                        //Decrements the size of the queue
    return object;                  //returns the removed node
}

bool PriorityQueue::isEmpty() const {
    return size_ == 0;              //Checks whether priority queue is empty or not and returns boolean value
}

size_t PriorityQueue::size() const {
    return size_;                  //Returns the current size of the queue
}

nlohmann::json PriorityQueue::JSON() const {
    nlohmann::json result;                  //Declare json function to display result
    for (size_t i = 1; i <= size_; i++) {   //The for loop is for iterating through each node and performing operations
        nlohmann::json node;
        KeyValuePair kv = nodes_[i];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT) {
            node["parent"] = std::to_string(i / 2); 
        }
        if (2 * i <= size_) {
            node["leftChild"] = std::to_string(2 * i);
        }
        if (2 * i + 1 <= size_) {
            node["rightChild"] = std::to_string(2 * i + 1);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
    return result;                         //returns a JSON representation of the priority queue by adding key, value and children to the result
}

void PriorityQueue::heapifyUp(size_t i) { 
        while (i > ROOT) {                              //Loop to check if i is greater than the root node
        size_t parent = i / 2;                          //calculates the index of the parent node of 
        if (nodes_[parent].first > nodes_[i].first) {   //checks whether the parent node has a higher priority value than the current node i
            std::swap(nodes_[parent], nodes_[i]);       //swap the parent node and the current node i.
            i = parent;                                 //sets i to the index of the parent that was swapped with node i.
        }
        else {               //else no change is made to the tree
            break;          //terminates loop
        }
    }
}

void PriorityQueue::heapifyDown(size_t i) {         
        while (2 * i <= size_) {            //loop which runs when index of the left child of node i is less than or equal to the current size of the heap.
        size_t child = 2 * i;               //sets child to index of i
        if (child + 1 <= size_ && nodes_[child + 1].first < nodes_[child].first) {      //checks if there is a right child of node i, and if it has a smaller key value than the left child. If so, then child is set to the index of the right child.
            ++child;         //increments child so that it points to the index of the smaller child.
        }
        if (nodes_[i].first > nodes_[child].first) {    //checks if the key value of node i is greater than the key value of its smaller child.
            std::swap(nodes_[i], nodes_[child]);        //swaps the positions of the nodes i and child.
            i = child;          //sets i to the index of the child that was swapped with node i.
        }
        else {                  //else no change is made to the tree
            break;              //terminates loop
        }
    }
}

void PriorityQueue::removeNode(size_t i) {
    nodes_[i] = nodes_[size()];     //replaces the node at index i with the last node in the heap
    if (i > size_) {        //checks if the index i is greater than the size of the heap
        return;             //returns since there is no node
    }
    nodes_.pop_back();      //removes the last element from the heap
    heapifyDown(i);         //Starting at index i, the function swaps the node with its smallest child until the heap property is restored.
    size_--;          //This decrements the size of the heap tp show removal of the node.
}

Key PriorityQueue::getKey(size_t i) {
    return nodes_[i].first;     //returns the key of the node at index i in the heap
}

Value PriorityQueue::getKey2(int i) {
    return nodes_[i].second;   //returns i-th element in the priority queue's internal vector nodes.
}
