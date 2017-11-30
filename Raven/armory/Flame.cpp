#include "Flame.h"
#include "../lua/Raven_Scriptor.h"
#include "misc/cgdi.h"
#include "../Raven_Bot.h"
#include "../Raven_Game.h"
#include "game/EntityFunctionTemplates.h"
#include "../constants.h"
#include "2d/WallIntersectionTests.h"
#include "../Raven_Map.h"
#include <list>

#include "../Raven_Messages.h"
#include "Messaging/MessageDispatcher.h"



Flame::Flame(Raven_Bot * shooter, Vector2D target):
	Raven_Projectile(target,
		shooter->GetWorld(),
		shooter->ID(),
		shooter->Pos(),
		shooter->Facing(),
		script->GetInt("Flame_Damage"),
		script->GetDouble("Flame_Scale"),
		script->GetDouble("Flame_MaxSpeed"),
		script->GetDouble("Flame_Mass"),
		script->GetDouble("Flame_MaxForce")),

	m_dTimeShotIsVisible(script->GetDouble("Flame_Persistance"))
{
}

void Flame::Render()
{
	gdi->RedPen();
	gdi->OrangeBrush();
	gdi->Circle(Pos(), 4);
}

void Flame::Update()
{
	if (!HasImpacted())
	{
		//calculate the steering force
		Vector2D DesiredVelocity = Vec2DNormalize(m_vTarget - Pos()) * MaxSpeed();

		Vector2D sf = DesiredVelocity - Velocity();

		//update the position
		Vector2D accel = sf / m_dMass;

		m_vVelocity += accel;

		//make sure vehicle does not exceed maximum velocity
		m_vVelocity.Truncate(m_dMaxSpeed);

		//update the position
		m_vPosition += m_vVelocity;

		TestForImpact();
	}
	else if (!isVisibleToPlayer())
	{
		m_bDead = true;
	}
}

void Flame::TestForImpact()
{

	
}