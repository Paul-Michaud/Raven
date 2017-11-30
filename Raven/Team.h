#ifndef TEAM_H
#define TEAM_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Team.h
//
//  Desc:
//-----------------------------------------------------------------------------

#include "Raven_Bot.h"
#include "TeamColor.h"


class Team {

private:

	std::list<Raven_Bot*> members;
	Raven_Bot* leader;
	Raven_Bot* target;

	TeamColor m_eTeamColor;

public:

	//Constructor
	Team(TeamColor teamColor);

	//Add member to the team
	void addMember(Raven_Bot*);

	//Assign a new leader for the team
	void setLeader(Raven_Bot*);

	//Assign a new leader for the team
	void setTarget(Raven_Bot*);

	// Set team's color
	void setTeamColor(TeamColor);

	// Set gdi color depending team
	void setGdiColor();

};


#endif