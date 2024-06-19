//bNaveed Sekender
#include <iostream>
#include <fstream>   //not sure if this is correct, we gotta check 
#include "json.hpp"
#include <algorithm>
#include <vector>
#include <iterator>

//make this simpler
using json = nlohmann::json;    // create a json object


using namespace std;

bool CheckJsonFiles_arethesame(const json &file1, const json &file2); //this is to check if the json files are the same
void show_differences(const json &file1, string file_1name,  const json &file2, string file_2name); //this is to show the differences between the files
 
 //this is to print out the json file 

//function to check if the data in both fo the JSON files are the exact same
bool CheckJsonFiles_arethesame(const json &file1, const json &file2){
    if (file1 == file2){ //if the files are the same
        return true; //return true
    }
    else{ //else
        return false; //return false
    }
}


//this function shows the differences between the files
void show_differences(const json &file1, string file_1name,  const json &file2, string file_2name){  //this function takes in two files as parameters
    vector <int> sample_1_differences;  //vector to store the differences between the samples
    vector <int> sample_2_differences;  //vector to store the differences between the samples
    vector <int> sample_1_diff;         //vector to store the differences between the samples
    vector <int> sample_2_diff;         //vector to store the differences between the samples

    json output_object;     //json object to store the output
    int mismatch_counter = 0;   //counter to keep track of the number of differences
    int index = 0;      //index to keep track of the number of differences
    bool meow = false;      //boolean to keep track of the number of differences
    sample_1_diff.emplace_back(0);  //to keep track of the number of differences
    sample_1_diff.emplace_back(0);  //to keep track of the number of differences

    for (auto it1 = file1.begin(),  it2 = file2.begin() ; it1 != file1.end(), it2 != file2.end(); ++it1,  ++ it2) { //so we will iterate over the file 1
        for (auto it3 = it1.value().begin(),  it4 = it2.value().begin() ; it3 != it1.value().end(), it4 != it2.value().end(); ++it3,  ++ it4) { //so we will iterate over the file 1
            if ( *it3 != *it4){
                meow = true; //this is a flag variabvle I rlly love cats
                output_object[it1.key()][file_1name] = it1.value(); //sample_1_diff
                output_object[it2.key()][file_2name] = it2.value(); //sample_
                sample_1_diff.at(0) = it1.value().at(index);    //sample_1_diff
                sample_1_diff.at(1) = it2.value().at(index);    //sample_1_diff
                output_object[it1.key()]["Mismatches"][to_string(index)] = sample_1_diff;   //mismatches

            }
            index ++;   //increment the index

        }
         index = 0;     //index to the next file
         if (meow) {    //if there is a mismatch
            mismatch_counter++; //increment the mismatch counter
         }
         meow = false;  //mismatched

    }
     //find out the indexes with differences   
     
     output_object["metadata"]["File1"]["arraySize"] = file1["metadata"]["arraySize"];  //arraySize
     output_object["metadata"]["File2"]["arraySize"] = file2["metadata"]["arraySize"];  //arraySize
     output_object["metadata"]["File1"]["name"] = file_1name;   //name
     output_object["metadata"]["File2"]["name"] = file_2name; //put in the name
     output_object["metadata"]["File1"]["numSamples"] = file1["metadata"]["numSamples"];   //name
     output_object["metadata"]["File2"]["numSamples"] = file2["metadata"]["numSamples"]; //put in the meta data
        //name

     output_object["metadata"]["samplesWithConflictingResults"] = mismatch_counter; //mismatches

    cout << output_object.dump(2)<< std::endl; //cout the output object
    

}




///YOSHI HERE 
int main(int argc, char** argv){


//check if the files exist
    ifstream json_file(argv[1]); //save the arg1 intothe json
    if (!json_file.is_open()) { //if it cant open 
        cerr << "Error: unable to open file " << argv[1] << endl; //say you cant open it
        return 1;
    }
    ifstream json_file_1(argv[2]); //save the arg1 intothe json
    if (!json_file_1.is_open()) { //if it cant open 
        cerr << "Error: unable to open file " << argv[2] << endl; //say you cant open it
        return 1;
    }


//create 2 objects of nlhomann class
    json fileJasonObj;     // objects that stores the info from the 1st file1 after its read
    ifstream file1(argv[1]); //scan the file1 in 
    file1 >> fileJasonObj;  //put it inside
    json file2JasonObj;    // object tat stores the infor fromt eh 2nd file1 after its read
    ifstream file2(argv[2]);//scan the file2 in 
    file2 >> file2JasonObj; //put it inside

// we will check if the json files are the same
    if(CheckJsonFiles_arethesame(fileJasonObj, file2JasonObj)){ //if they are trhe same
        cout << "These are the same" << endl; //say they are the same
        return 0; //kill program 
    }

    show_differences(fileJasonObj,argv[1], file2JasonObj, argv[2]); //call the function to show the difference

}