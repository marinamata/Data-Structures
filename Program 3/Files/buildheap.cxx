#include <iostream>
#include "priorityqueue.h"
#include "json.hpp"
#include <fstream>

// takes in integer and return the key for it
std::string textJson(int i) {   
    std::string key = "Op";     //initializes key with the value "Op".
    if (i < 10) {               //i is less than 10,
        key += "00";            //the string "00" is added to the key
    } 
    else if (i < 100) {       //i is less than 100,
        key += "0";             //the string "0" is added to the key variable.
    }
    key += std::to_string(i);   //appends integer i to the key string.
    return key;                 //returns value of key
}

int main(int argc, char **argv) {
    std::ifstream readFile;      //declares file streams
    nlohmann::json jsonObject;   //object to hold json data from input file
    nlohmann::json outputObject; //object to hold json outputs

    // put all data from JSON file into the json object
    readFile.open(argv[1]);      //open the json file
    if (readFile.is_open()) {      //checks whether file is open
        readFile >> jsonObject;  //operator overloading to store input from json file to json object
    }

    PriorityQueue priorityQueue((size_t)(jsonObject["metadata"]["maxHeapSize"])); //priorityque obejct to match up rest

    //operations on the priorityqueue data to insert or remove nodes
    int operationlines = jsonObject["metadata"]["numOperations"]; //extracts the value of the numOperations field in the metadata object and stores it in the variable operationlines.
    for (int i = 1; i <= operationlines; i++) {     //execute for operationlines and read through each value extracted above
        std::string operation = textJson(i);        //calls key value and stores in a string
        nlohmann::json value = jsonObject[operation]; //extracts the object corresponding to the operation key and stores it in the value variable.
        if (value["operation"] != "insert") {         //if values of operation string don't match,
            priorityQueue.removeMin();                //we call removemin
        } 
        else {                                      //else
            priorityQueue.insert((double)value["key"]); //it retrieves the value of the key field in the value JSON object, casts it to a double, and passes it to the insert method of the priorityQueue object.
        }
    }

    //get the results into the output object    //match output on Frid's pdf
    outputObject = priorityQueue.JSON();     //gets a JSON representation of the heap's contents
    outputObject["metadata"]["numOperations"] = operationlines;     //sets the numOperations field in the metadata object of outputObject to the value of operationlines.
    outputObject["metadata"]["maxHeapSize"] = jsonObject["metadata"]["maxHeapSize"];        //sets the maxHeapSize field in the metadata object of outputObject to the value of maxHeapSize in jsonObject.
    std::cout << outputObject.dump(2) << std::endl;     //prints the JSON representation
}