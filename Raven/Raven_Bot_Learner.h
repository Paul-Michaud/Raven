#pragma once
#include "Raven_Bot.h"
#include "debug/DebugConsole.h"
#include "Raven_WeaponSystem.h"
#include "armory/Raven_Weapon.h"
#include "debug/DebugConsole.h"
#include <vector>

using namespace std;


class Raven_Bot_Learner : public Raven_Bot 
{
public:
	Raven_Bot_Learner(Raven_Game* world, Vector2D pos, std::list<Raven_Bot*> &m_Bots);
	void         Update();
	void		saveData();

	~Raven_Bot_Learner();


private:
	std::list<Raven_Bot*> &m_Bots;


};

