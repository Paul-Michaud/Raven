#pragma once
#include "Raven_Bot.h"
#include "debug/DebugConsole.h"
#include "Raven_WeaponSystem.h"
#include "armory/Raven_Weapon.h"
#include "debug/DebugConsole.h"
#include <vector>
#include "Perceptron.hpp"
#include "goals/Goal_Think.h"
#include "time/Regulator.h"
#include "Raven_SensoryMemory.h"
#include "Raven_UserOptions.h"



using namespace std;


class Raven_Bot_Learner : public Raven_Bot 
{
public:
	Raven_Bot_Learner(Raven_Game* world, Vector2D pos, std::list<Raven_Bot*> &m_Bots);
	void         Update();
	void		saveData();
	ofstream	dataFile;

	void trainPerceptron();
	void testPerceptron();

	~Raven_Bot_Learner();
	void Render();

private:
	Perceptron *perceptron;

	std::list<Raven_Bot*> &m_Bots;

};

