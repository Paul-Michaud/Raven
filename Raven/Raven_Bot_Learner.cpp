#include "Raven_Bot_Learner.h"
#include <iostream>
#include <vector>


using namespace std;



Raven_Bot_Learner::Raven_Bot_Learner(Raven_Game* world, Vector2D pos, std::list<Raven_Bot*> &bots):Raven_Bot(world, pos), m_Bots(bots) {

	ifstream file("Data/LearningData.csv");
	string value;
	while (file.good()) {
		getline(file, value);

		string line = value;
		string arr[6];
		int i = 0;
		stringstream ssin(line);
		while (ssin.good() && i < 6) {
			ssin >> arr[i];
			++i;
		}
		
			debug_con << arr[0] << "";
			debug_con << arr[1] << "";
			debug_con << arr[2] << "";
			debug_con << arr[3] << "";
			debug_con << arr[4] << "";
			debug_con << arr[5] << "";

		debug_con << "NEXT" << "";

	}

}

void Raven_Bot_Learner::Update() {

	//saveData();

	Raven_Bot::Update();
}

void Raven_Bot_Learner::saveData() {

	std::list<Raven_Bot*>::const_iterator curBot = m_Bots.begin();
	//Learn from only 1 bot for the moment

	if ((*curBot) == this) curBot++;

	//saving data to learn
	double DistToTarget = 0;
	double TimeTargetHasBeenVisible = 0;

	if ((*curBot)->GetTargetSys()->GetTarget()) {
		DistToTarget = Vec2DDistance((*curBot)->Pos(), (*curBot)->GetTargetSys()->GetTarget()->Pos());
		TimeTargetHasBeenVisible = (*curBot)->GetTargetSys()->GetTimeTargetHasBeenVisible();
	}

	double Velocity = (*curBot)->Speed();

	bool HasFired = (*curBot)->GetFiredStatus();
	if ((*curBot)->GetFiredStatus()) (*curBot)->SetFiredStatus(false);

	int WeaponType = (*curBot)->GetWeaponSys()->GetCurrentWeapon()->GetType();

	double Ammo = (double)(*curBot)->GetWeaponSys()->GetAmmoRemainingForWeapon(WeaponType);


	//debug_con << "DistToTarget : " << DistToTarget << "";
	//debug_con << "Velocity : " << Velocity << "";
	//debug_con << "TimeTargetHasBeenVisible : " << TimeTargetHasBeenVisible << "";
	//debug_con << "HasFired : " << HasFired << "";
	//debug_con << "WeaponType : " << WeaponType << "";
	//debug_con << "Ammo : " << Ammo << "";
	//debug_con << "----------------------------------" << "";
	//debug_con << "                UPDATE             " << "";
	//debug_con << "----------------------------------" << "";


	std::vector<double> data;

	data.push_back(DistToTarget);
	data.push_back(Velocity);
	data.push_back(TimeTargetHasBeenVisible);
	data.push_back((double)HasFired);
	data.push_back((double)WeaponType);
	data.push_back(Ammo);


	ofstream dataFile;
	dataFile.open("Data/LearningData.csv", std::ofstream::app);

	for (auto it = data.begin(); it != data.end(); ++it) {
		dataFile << std::fixed << std::setprecision(2) << *it;
		if (std::next(it) != data.end())  dataFile << " ";		
	}
	dataFile << "\n";
	dataFile.close();



}
Raven_Bot_Learner::~Raven_Bot_Learner(){

}
