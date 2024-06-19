#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_

#include <vector>
#include <utility>
#include "json.hpp"

typedef double                  Key;          //type double
typedef std::pair<int, int>     Value;        //pair of two integers
typedef std::pair<Key, Value>   KeyValuePair; //pair of key and value

class PriorityQueue {
  public:
    PriorityQueue(std::size_t max_nodes); //specifies the maximum number of nodes that can be stored in the priority queue.
    void insert(Key k);                   //inserts a key into the priority queue.
    void insert(KeyValuePair kv);         //inserts a key-value pair into the priority queue.
    KeyValuePair min();                   //returns the key-value pair with the minimum key in the priority queue.
    KeyValuePair removeMin();             //removes and return the key-value pair with the minimum key in the priority queue.
    bool isEmpty() const;                 //check if the priority queue is empty.
    size_t size() const;                  //returns the current number of nodes in the priority queue.
    nlohmann::json JSON() const;          //returns a json object representing the priority queue.               
    void removeNode(size_t i);            //removes a node at a given index in the heap.
    Value getKey2(int i);                 //method to retrieve the value of a node at a given index in the heap.

  private:
    void heapifyUp(size_t i);   //maintain the heap property by moving a node up the tree when necessary.
    void heapifyDown(size_t i); //maintain the heap property by moving a node down the tree when necessary.
    Key getKey(size_t i);       //to retrieve the key of a node at a given index in the heap.

    std::vector<KeyValuePair>   nodes_;       //represents the nodes in the priority queue.
    size_t                      max_size_;    //maximum number of nodes that can be stored in the priority queue.
    size_t                      size_;        //current number of nodes in the priority queue.

    const static size_t         ROOT = 1;     //represents the index of the root node
};  // class PriorityQueue

#endif  // _PRIORITYQUEUE_H_