#ifndef TEAM_H
#define TEAM_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Bot.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:
//-----------------------------------------------------------------------------

#include "Raven_Bot.h"



class Team {

private:

	std::list<Raven_Bot*> members;
	Raven_Bot* leader;
	Raven_Bot* target;

public:

	//Constructor
	Team();

	//Add member to the team
	void addMember(Raven_Bot*);

	//Assign a new leader for the team
	void setLeader(Raven_Bot*);

	//Assign a new leader for the team
	void setTarget(Raven_Bot*);

	//void setGdiContext()

};


#endif