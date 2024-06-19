#include <iostream>
#include "priorityqueue.h"
#include "teamdata.h"

int main(int argc, char** argv) {
    nlohmann::json outputObject;    //Creates an empty JSON object
    TeamData teamData(argv[1]);     //Instantiates the TeamData object with the command-line argument passed as a filename.
    std::vector<std::vector<int>> allTeams;     //Creates an empty 2D integer vector allTeams.
    PriorityQueue priorityQueue(teamData.numPlayers());     //Instantiates the PriorityQueue object with the number of players in the team.

    //Insert all winPercentages into the priority queue

    std::for_each(teamData.winPercentages_.begin(), teamData.winPercentages_.end(), 
        [&priorityQueue](const pairedteams & winPercentage) {  //Iterates through each pairedteams object in the winPercentages_ vector using std::for_each algorithm
            priorityQueue.insert(winPercentage); //Inserts each pairedteams object into the priorityQueue.
        }); 

    while (!priorityQueue.isEmpty()) { //executes while the priority queue is not empty.
    pairedteams result = priorityQueue.removeMin();    //Removes the pairedteams object with the smallest first element and assigns it to result.
    std::vector<int> team1 = {result.second.first, result.second.second};  //Creates a vector team1 with the player 1 and player 2 integers from resultPair
    allTeams.push_back(team1);      //Adds team1 to the end of allTeams.

    for (int i = 1; i <= (int)priorityQueue.size(); i++) {  //Starts a for loop which iterates through every node in the priority queue.
        bool First_FirstPriority;   //true if the first player of the first team in the current key pair matches the first player of the team that was just removed from the queue.
        bool First_SecondPriority;  //true if the first player of the first team in the current key pair matches the second player of the team that was just removed from the queue.
        bool Second_FirstPriority;  //true if the second player of the first team in the current key pair matches the first player of the team that was just removed from the queue.
        bool Second_SecondPriority; // true if the second player of the first team in the current key pair matches the second player of the team that was just removed from the queue.

        auto key2 = priorityQueue.getKey2(i);   //Gets the second key of the node at index i.
        int first_key2 = key2.first;        //Gets the first element of key2 and assigns it to first_key2.
        int second_key2 = key2.second;      //Gets the second element of key2 and assigns it to second_key2.
        First_FirstPriority = first_key2 == result.second.first;    //Compares first_key2 with resultPair.second.first and assigns the result to First_FirstPriority.
        First_SecondPriority = first_key2 == result.second.second;  //Compares first_key2 with resultPair.second.second and assigns the result to First_SecondPriority.
        Second_FirstPriority = second_key2 == result.second.first;  //Compares second_key2 with resultPair.second.first and assigns the result to Second_FirstPriority.
        Second_SecondPriority = second_key2 == result.second.second;//Compares second_key2 with resultPair.second.second and assigns the result to Second_SecondPriority.

        if (First_FirstPriority || First_SecondPriority || Second_FirstPriority || Second_SecondPriority) { //Check if any team has been repeated
            priorityQueue.removeNode(i);    //remove the node at index i from the priority queue.
            i--;
        }
    }
}
    outputObject["teams"] = allTeams;        //sets the "teams" field of the outputObject to the vector allTeams 
    std::cout << outputObject.dump(2) << std::endl;      //prints the JSON representation
}