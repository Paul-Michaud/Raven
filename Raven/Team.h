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

	std::list<Raven_Bot*> m_members;
	Raven_Bot* m_pLeader;
	Raven_Bot* m_pTarget;

	TeamColor m_eTeamColor;

public:

	//Constructor
	Team(TeamColor teamColor);

	//Add member to the team
	void addMember(Raven_Bot*);

	//Remove particular member of the team
	void removeMember(Raven_Bot*);

	//Assign a new leader for the team
	void setLeader(Raven_Bot*);

	Raven_Bot* getLeader() { return m_pLeader; }

	//Assign a new leader for the team
	void setTarget(Raven_Bot*);

	// Set team's color
	void setTeamColor(TeamColor);

	// Set gdi color depending team (Brush)
	void setGdiBrushColor();

	// Set gdi color depending team (Pen)
	void setGdiPenColor();

	//Check if team has an active leader
	bool hasActiveLeader();

	//Check if a bot is the leader
	bool isLeader(Raven_Bot*);

	//Set leader with first active bot
	void setLeaderWithFirstActiveBot();

	//Get the number of bots in team
	int getNumberOfBots();

	//Get the team's target
	Raven_Bot* getTarget() { return m_pTarget; }

};


#endif