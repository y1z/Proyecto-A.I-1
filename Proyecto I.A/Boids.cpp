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

void Boids::Seek(CVector2D & OtherPoint)
{

	while (true) {
		
		

		DumbStop();
	}


}
