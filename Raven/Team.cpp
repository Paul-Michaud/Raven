#include "Team.h"
#include "misc/Cgdi.h"


//-----------------------
//     Constructor
//-----------------------
Team::Team(TeamColor teamColor){
	
	setTeamColor(teamColor);
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


// Set gdi color depending team
//-----------------------
void Team::setGdiColor() {
	
	switch (m_eTeamColor){
		case TeamColor::BLUE:
			gdi->BluePen();
			break;
		case TeamColor::GREEN:
			gdi->GreenPen();
			break;
		case TeamColor::GREY:
			gdi->GreyPen();
			break;
		case TeamColor::PINK:
			gdi->PinkPen();
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


