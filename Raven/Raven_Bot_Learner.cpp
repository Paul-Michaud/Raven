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

	//process the currently active goal. Note this is required even if the bot
	//is under user control. This is because a goal is created whenever a user 
	//clicks on an area of the map that necessitates a path planning request.
	m_pBrain->Process();
	
	//Calculate the steering force and update the bot's velocity and position
	UpdateMovement();

	//if the bot is under AI control but not scripted
	if (!isPossessed())
	{
		//examine all the opponents in the bots sensory memory and select one
		//to be the current target
		if (m_pTargetSelectionRegulator->isReady()) {

			//If this bot is not in a team or is the leader of his team
			if (m_pTeam == NULL || m_pTeam->isLeader(this)) {

				m_pTargSys->Update();

				//If it has a team, update the target
				if (m_pTeam != NULL) m_pTeam->setTarget(m_pTargSys->GetTarget());

			}

		}
		//If bot has a team and is not the leader and there is a leader in the team
		else if (m_pTeam != NULL && !m_pTeam->isLeader(this) && m_pTeam->getLeader() != NULL) {

			m_pTargSys->SetCurrentTarget(m_pTeam->getLeader()->GetmTargetSystem()->GetTarget());
		}

		//appraise and arbitrate between all possible high level goals
		if (m_pGoalArbitrationRegulator->isReady())
		{
			m_pBrain->Arbitrate();
		}

		//update the sensory memory with any visual stimulus
		if (m_pVisionUpdateRegulator->isReady())
		{
			m_pSensoryMem->UpdateVision();
		}

		//select the appropriate weapon to use from the weapons currently in
		//the inventory
		if (m_pWeaponSelectionRegulator->isReady())
		{
			m_pWeaponSys->SelectWeapon();
		}


		double DistToTarget = 0;
		double TimeTargetHasBeenVisible = 0;

		if (this->GetTargetSys()->GetTarget()) {
			DistToTarget = Vec2DDistance(this->Pos(), m_pTargSys->GetTarget()->Pos());
			TimeTargetHasBeenVisible = m_pTargSys->GetTimeTargetHasBeenVisible();
		}

		double Velocity = this->Speed();

		double WeaponType = m_pWeaponSys->GetCurrentWeapon()->GetType();

		double Ammo = m_pWeaponSys->GetAmmoRemainingForWeapon(WeaponType);

		bool result = (*perceptron).get_result({ DistToTarget, Velocity, TimeTargetHasBeenVisible, WeaponType, Ammo });

			
		m_pWeaponSys->TakeAimAndShootLearner(result);

	}

	saveData();
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

//--------------------------- Render -------------------------------------
//
//------------------------------------------------------------------------
void Raven_Bot_Learner::Render()
{
	//when a bot is hit by a projectile this value is set to a constant user
	//defined value which dictates how long the bot should have a thick red
	//circle drawn around it (to indicate it's been hit) The circle is drawn
	//as long as this value is positive. (see Render)
	m_iNumUpdatesHitPersistant--;


	if (isDead() || isSpawning()) return;

	if (m_pTeam != NULL) m_pTeam->setGdiPenColor();
	else gdi->BluePen();

	m_vecBotVBTrans = WorldTransform(m_vecBotVB,
		Pos(),
		Facing(),
		Facing().Perp(),
		Scale());

	gdi->ClosedShape(m_vecBotVBTrans);

	//draw the head
	if (m_pTeam != NULL) m_pTeam->setGdiBrushColor();
	else gdi->BrownBrush();
	gdi->Circle(Pos(), 6.0 * Scale().x);


	//render the bot's weapon
	m_pWeaponSys->RenderCurrentWeapon();

	//render a thick red circle if the bot gets hit by a weapon
	if (m_bHit)
	{
		gdi->ThickRedPen();
		gdi->HollowBrush();
		gdi->Circle(m_vPosition, BRadius() + 1);

		if (m_iNumUpdatesHitPersistant <= 0)
		{
			m_bHit = false;
		}
	}

	gdi->TextColor(85, 26, 139);
	gdi->TextAtPos(Pos().x+15, Pos().y-5, "Learner");
	gdi->TransparentText();
	gdi->TextColor(0, 255, 0);

	if (UserOptions->m_bShowBotIDs)
	{
		gdi->TextAtPos(Pos().x - 10, Pos().y - 20, ttos(ID()));
	}

	if (UserOptions->m_bShowBotHealth)
	{
		gdi->TextAtPos(Pos().x - 40, Pos().y - 5, "H:" + ttos(Health()));
	}

	if (UserOptions->m_bShowScore)
	{
		gdi->TextAtPos(Pos().x - 40, Pos().y + 10, "Scr:" + ttos(Score()));
	}
}

Raven_Bot_Learner::~Raven_Bot_Learner(){
	dataFile.close();

}
