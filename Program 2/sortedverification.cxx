//naveed Sekender
#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
        

//define the functions 
bool checkInversion(vector<int> object); //this is the check iversion 
void edit_json(vector<int> object, string sample, nlohmann:: json &output); //this is to edit the json object


//check for inversions
bool checkInversion(vector<int> object){ //pass in vector of objects
    //add the number to json object
    for (int i = 1; i < object.size(); i++){ //we look through object and check if there are any inversions
        if (object[i -1] > object[i]){ //if the number before is less
            return true;  //if there is an iversion we return true 
        }
    }
    return false;  //else we will return false
}

void edit_json(vector<int> object, string sample, nlohmann:: json &output){ //pass in vector of object and the file so we can edit it
    for (int i = 1; i < object.size(); i++){ //look through object and see
        if (object[i - 1] > object[i]){ //if the number before is less
            // then we add a function call Consecutive iversions
            output[sample]["ConsecutiveInversions"][to_string(i-1)] = {object[i - 1], object[i]}; //convert the i into a string to make it save!
        }
    } 

}


int main(int argc, char** argv) { //this is the 

    std::ifstream json_file(argv[1]); //argv1 into the object
    if (!json_file.is_open()) { //if it cant open 
        std::cerr << "Error: unable to open file " << argv[1] << std::endl; //explain that you can't continue
        return 1;   //return 1

    }

    nlohmann::json outputObject;  //creating the object that prints out the results
    nlohmann::json test;    //creating the object that prints out the results
    json_file >> test;  //reading the json file


   
    
    int number_of_samples_with_iversions = 0; //number of inversions

        //after the check file itereate through it and 
    for (auto itr = test.begin(); itr != test.end(); itr++){ //this is an iteratr to look through the entire file
        if (itr.key() != "metadata"){ //if the key is not metadata then it
            if (checkInversion(itr.value())){ //if there is an iversion
                    edit_json(itr.value(), itr.key(), outputObject);   //we will edit the json object
                    outputObject[itr.key()]["sample"] = itr.value();    //this  will make the sample the same as the iterator value
                    number_of_samples_with_iversions++; //if we find a sample with an inversion it will increment the number of samples
            }
        }
    }    

    outputObject["metadata"] = test["metadata"]; //set the meta data
    outputObject["metadata"]["file"] = argv[1]; //set the file name
    outputObject["metadata"]["samplesWithInversions"] = number_of_samples_with_iversions; //set the number of samples with an inversion

    
    std::cout << outputObject.dump(2)<< std::endl;  //output the object

    return 0; //kill the program

}