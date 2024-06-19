#include "teamdata.h"
#include <fstream>
#include <iostream>
#include <cmath>

TeamData::TeamData(std::string filename) {
    // read the json file and put the data into the object
    std::ifstream readFile;         //declares file streams
    nlohmann::json jsonObject;      //object to hold json data from input file
    readFile.open(filename);        //open the json file
    if (readFile.is_open()) {       //checks whether file is open
        readFile >> jsonObject;     //operator overloading to store input from json file to json object
    }

    // get the number of players
    numPlayers_ = jsonObject["metadata"]["numPlayers"];     //get number of players from jsonobject

    // get the team stats array
    nlohmann::json teamStats;               //stores the teams statistics
    teamStats = jsonObject["teamStats"];    //gets team stats array from jsonobject

    // read all the team data and push it into the winPercentages_ vector
    std::transform(teamStats.begin(), teamStats.end(), std::back_inserter(winPercentages_), [this](const auto& teamStat) { //iterates over the team stats array and creates a pairedteams object for each team. Can be subbed for a for loop
        //create a team pair with win percentages
        pairedteams teamPair;   //stores team data
        winPercentage percentage = teamStat["winPercentage"];   //gets win percentage of team

        //get player 1 and player 2
        int player1 = teamStat["playerOne"]; //player 1
        int player2 = teamStat["playerTwo"]; //player 2

        //put player1 and 2 into "playerTeam"
        teams playerTeam;   //stores players in the team
        playerTeam.first = player1;     //gets the first player for team
        playerTeam.second = player2;    //gets the second player for team

        // team winning percentage to see which team has the percentage closest to 50%
        teamPair.first = std::abs((double)(50.00 - percentage)); //calculates team's win percentage 
        teamPair.second = playerTeam;   //stores players in team to teamPair.second 
        return teamPair;
    });
}

// return the number of players in the team
int TeamData::numPlayers() const {
    return numPlayers_;     //returns players
}