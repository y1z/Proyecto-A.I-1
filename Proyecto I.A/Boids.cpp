#include "Boids.h"
#include "HelperFunctions.h"


Boids::Boids()
{
	m_speed = 1.0f;
	m_position.SetX(0);
	m_position.SetY(0);
	m_direction.SetX(0);
	m_direction.SetY(0);
}


Boids::~Boids()
{
}

void Boids::SetPosition(float x, float y)
{
	m_position.SetX(x);
	m_position.SetY(y);
}

void Boids::Seek(CVector2D &StartVector, CVector2D & EndPoint)
{
	float SeekForce = 0.50f;

	CVector2D Position = StartVector;
	CVector2D ChangeInForce(-0,-0);
	CVector2D MovingForce;

	/*! find out where to go */
	CVector2D TragetVector = EndPoint - StartVector;

	std::cout << "Heres the starting vector " << StartVector 
		<< "Here is the objective " << EndPoint << "\n\n";

	std::cout << "here is the distance = " << TragetVector << "\n";

	while (true) {

		CVector2D TragetVector = EndPoint - StartVector;

		/*! used to make boid not go to far away from target*/
		ChangeInForce = TragetVector - Position;

		ChangeInForce += ChangeInForce.Normalize() * SeekForce;

		/*!*/
		MovingForce += ChangeInForce;
		
		Position += MovingForce;

		std::cout << Position <<'\n';
		std::cout << "change in force = " << ChangeInForce << "\n";
		
		DumbStop();
	}


}

void Boids::flee(CVector2D & StartVector, CVector2D & DangerVector, float RangeOfDanger)
{

	float SeekForce = 1.f;

	CVector2D Position = StartVector;
	CVector2D ChangeInForce(-0, -0);
	CVector2D MovingForce;

	/*! find out where to go */
	CVector2D TragetVector = DangerVector - StartVector;

	CVector2D DangerZone = DangerVector.Normalize() * RangeOfDanger;

	std::cout << "Heres the starting vector " << StartVector
		<< "Here is the objective " << DangerVector << "\n\n";

	std::cout << "here is the distance = " << TragetVector << "\n";

	while (true) {

		CVector2D TragetVector = DangerVector - StartVector;

		if( (Position - (DangerVector + DangerZone)).Magnitude() < DangerZone.Magnitude())
		{
			std::cout << "WHAT'S UP DANGERRRR \n";
			ChangeInForce = Position - TragetVector;
		}
		else
		{
			/*! used to make boid not go to far away from target*/
			ChangeInForce = TragetVector - Position;
		}

		ChangeInForce += ChangeInForce.Normalize() * SeekForce;

		/*!*/
		MovingForce += ChangeInForce;

		Position += MovingForce;

		std::cout << Position << '\n';
		std::cout << "change in force = " << ChangeInForce << "\n";

		DumbStop();
	}

}
