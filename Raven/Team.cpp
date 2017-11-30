#include "Team.h"


//-----------------------
//     Constructor
//-----------------------
Team::Team(){
}

//-----------------------
// Add member to the team
//-----------------------
void Team::addMember(Raven_Bot* member){
	members.push_back(member);
}

//-----------------------
// Assign a new leader for the team
//-----------------------
void Team::setLeader(Raven_Bot* leader){
	leader = leader;
}

//-----------------------
// Assign a new leader for the team
//-----------------------
void Team::setTarget(Raven_Bot* target){
	target = target;
}


