#include "Raven_Bot_Learner.h"
#include <iostream>
#include <vector>


using namespace std;



Raven_Bot_Learner::Raven_Bot_Learner(Raven_Game* world, Vector2D pos, std::list<Raven_Bot*> &bots):Raven_Bot(world, pos), m_Bots(bots) {
	dataFile.open("Data/LearningData.csv", std::ofstream::app);

	trainPerceptron();
	testPerceptron(); 

}

void Raven_Bot_Learner::Update() {

	//saveData();

	Raven_Bot::Update();
}

void Raven_Bot_Learner::saveData() {
	//Save data from only 1 bot for the moment

	std::list<Raven_Bot*>::const_iterator curBot = m_Bots.begin();
	std::vector<double> dataToSave;

	//We don't want to learn from ourself
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

	

	dataToSave.push_back((double)HasFired);
	dataToSave.push_back(DistToTarget);
	dataToSave.push_back(Velocity);
	dataToSave.push_back(TimeTargetHasBeenVisible);
	dataToSave.push_back((double)WeaponType);
	dataToSave.push_back(Ammo);

	for (auto it = dataToSave.begin(); it != dataToSave.end(); ++it) {
		dataFile << std::fixed << std::setprecision(2) << *it;
		if (std::next(it) != dataToSave.end())  dataFile << " ";
	}
	dataFile << "\n";
	
}

void Raven_Bot_Learner::trainPerceptron() {
	ifstream learningFile("Data/LearningData.csv");

	string value;
	//Used to convert string to bool
	bool hasFired;
	std::vector<TrainingItem> training_set;
	string line;
	string arr[6];
	int i = 0;
	perceptron = new Perceptron(5);


	if (learningFile.is_open()) {
		while (learningFile.good()) {
			getline(learningFile, value);

			if (!value.empty()) {
				line = value;
				i = 0;
				stringstream ssin(line);
				while (ssin.good() && i < 6) {
					ssin >> arr[i];
					++i;
				}

				//Convert string to bool
				istringstream(arr[0]) >> hasFired;

				//HasFired, DistToTarget, Velocity, TimeTargetHasBeenVisible, WeaponType, Ammo
				TrainingItem tempTrainingItem = TrainingItem(hasFired, { stod(arr[1]), stod(arr[2]), stod(arr[3]), stod(arr[4]),stod(arr[5]) });
				training_set.push_back(tempTrainingItem);
			}
		}
		debug_con << "Training set created" << "";

		(*perceptron).train(training_set, 20);
		debug_con << "Perceptron trained" << "";
	}
	else {
		debug_con << "File Data/LearningData.csv not found or unable to open" << "";
		debug_con << "perceptron NOT trained" << "";


	}
}

void Raven_Bot_Learner::testPerceptron() {

	string value;
	int cptr = 0;
	int ok = 0;

	string line;
	string arr[6];
	int i = 0;

	//Used to convert string to bool
	bool hasFired;

	//TESTS

	//creation des items de tests

	ifstream testfile("Data/TestData.csv");
	if (testfile.is_open()) {
		cptr = 0;
		ok = 0;
		while (testfile.good()) {
			getline(testfile, value);

			if (!value.empty()) {
				line = value;
				i = 0;
				stringstream ssin(line);
				while (ssin.good() && i < 6) {
					ssin >> arr[i];
					++i;
				}

				cptr++;

				istringstream(arr[0]) >> hasFired;

				//HasFired, DistToTarget, Velocity, TimeTargetHasBeenVisible, WeaponType, Ammo
				if ((*perceptron).get_result({ stod(arr[1]), stod(arr[2]), stod(arr[3]), stod(arr[4]),stod(arr[5]) }) == hasFired) ok++;

			}
		}

		debug_con << "Model accuracy : " << (float)ok / (float)cptr*100.0 << "%" << "";
	}
	else {
		debug_con << "File Data/TestData.csv not found, or unable to open" << "";

	}

}
Raven_Bot_Learner::~Raven_Bot_Learner(){
	dataFile.close();

}
