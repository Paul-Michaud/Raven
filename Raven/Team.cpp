#include "Team.h"
#include "misc/Cgdi.h"


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



