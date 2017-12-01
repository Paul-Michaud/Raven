#include "Team.h"
#include "misc/Cgdi.h"

#include "debug/DebugConsole.h"


//-----------------------
//     Constructor
//-----------------------
Team::Team(TeamColor teamColor){
	
	setTeamColor(teamColor);
	m_pLeader = NULL;
	m_pTarget = NULL;
}

//-----------------------
// Add member to the team
//-----------------------
void Team::addMember(Raven_Bot* member){
	m_members.push_back(member);
	member->setTeamMembership(this);
}

//-----------------------
// Assign a new leader for the team
//-----------------------
void Team::setLeader(Raven_Bot* leader){
	m_pLeader = leader;
}

//-----------------------
// Assign a new leader for the team
//-----------------------
void Team::setTarget(Raven_Bot* target){
	target = target;
}


// Set gdi color depending team (Brush)
//-----------------------
void Team::setGdiBrushColor() {
	
	switch (m_eTeamColor){
		case TeamColor::BLUE:
			gdi->BlueBrush();
			break;
		case TeamColor::RED:
			gdi->RedBrush();
			break;
		case TeamColor::GREEN:
			gdi->GreenBrush();
			break;
		case TeamColor::GREY:
			gdi->GreyBrush();
			break;
		case TeamColor::YELLOW:
			gdi->YellowBrush();
			break;
		case TeamColor::ORANGE:
			gdi->OrangeBrush();
			break;
		default:
			gdi->BlueBrush();
			break;
	}

}

// Set gdi color depending team (Pen)
//-----------------------
void Team::setGdiPenColor() {

	switch (m_eTeamColor) {
	case TeamColor::BLUE:
		gdi->BluePen();
		break;
	case TeamColor::RED:
		gdi->RedPen();
		break;
	case TeamColor::GREEN:
		gdi->GreenPen();
		break;
	case TeamColor::GREY:
		gdi->GreyPen();
		break;
	case TeamColor::YELLOW:
		gdi->YellowPen();
		break;
	case TeamColor::ORANGE:
		gdi->OrangePen();
		break;
	default:
		gdi->BluePen();
		break;
	}

}

// Set team's color
//-----------------------
void Team::setTeamColor(TeamColor teamColor) {
	m_eTeamColor = teamColor;
}

//Check if team has an active leader
//----------------------------------
bool Team::hasActiveLeader() {
	return m_pLeader != NULL && ! m_pLeader->isDead() && ! m_pLeader->isSpawning();
}

//Check if a bot is the leader
//----------------------------
bool Team::isLeader(Raven_Bot* bot) {
	return bot == m_pLeader;
}


//Set leader with first active bot
//--------------------------------
void Team::setLeaderWithFirstActiveBot() {
	
	for (std::list<Raven_Bot*>::iterator it = m_members.begin(); it != m_members.end(); ++it) {
		if (!(*it)->isDead() && !(*it)->isSpawning()) {
			setLeader(*it);
			return;
		}
	}

}

//Get the number of bots in team
//------------------------------
int Team::getNumberOfBots() {
	return m_members.size();
}


//Remove particular member of the team
//------------------------------------
void Team::removeMember(Raven_Bot* bot) {
	
	m_members.remove(bot);

	if (bot == m_pLeader) {
		m_pLeader = NULL;
		m_pTarget = NULL;
	}

}

//Check if a bot is in this team with his ID
//------------------------------------
bool Team::isInTeam(int id) {
	for (std::list<Raven_Bot*>::iterator it = m_members.begin(); it != m_members.end(); ++it) {
		if ((*it)->ID() == id) return true;
	}
	return false;
}


