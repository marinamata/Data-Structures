#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_

#include <string>
#include <vector>
#include "json.hpp"

//defined vectors for easier implementation
typedef double winPercentage;							//define percentage wins
typedef std::pair<int, int> teams;						//defines teams
typedef std::pair<winPercentage, teams> pairedteams;	//defines pairs of teams 

class TeamData {	//class
 public:
 	TeamData(std::string filename);		//declares filename
 	int numPlayers() const;				//declares number of players
   //double winPercentages(int i, int j) const { return winPercentages_};
   std::vector<pairedteams> winPercentages_;	//stores list of pairs of teams

 private:
 //	TODO: decide the type of this variable.
	int numPlayers_;		//stores number of players
};  // class TeamData

#endif  // _TEAMDATA_H_