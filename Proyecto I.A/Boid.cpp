#include "Boid.h"
#include "HelperFunctions.h"


Boid::Boid()
{
	m_speed = 1.0f;
	m_position.SetX(0);
	m_position.SetY(0);

	m_direction.SetX(0);
	m_direction.SetY(0);
}

Boid::~Boid()
{
}

bool Boid::Init(const CVector2D & Position, const CVector2D & Direction, float speed)
{
	m_position = Position;
	m_direction = Direction;
	m_speed = speed;

	return true;
}

void Boid::SetPosition(const CVector2D & Position)
{
	m_position = Position;
}

void Boid::SetDirection(const CVector2D & Direction)
{
	m_direction = Direction;
}

void Boid::SetSpeed(float speed)
{
	m_speed = speed;
}

float Boid::Distance(Boid & OtherBoid)
{
	return (this->m_position.SquaredMagnitude() - OtherBoid.m_position.SquaredMagnitude());
}

float Boid::Distance(CVector2D & OtherVector)
{
	return (OtherVector - this->m_position).SquaredMagnitude();
}

CVector2D Boid::GetPosition() //const
{
	return m_position;
}

CVector2D Boid::GetDirection() const
{
	return m_direction;
}

float Boid::GetSpeed()
{
	return m_speed;
}

CVector2D Boid::Seek(CVector2D *StartVector, CVector2D *Speed, CVector2D *EndPoint)
{


	CVector2D TragetVector = (*EndPoint) - (*StartVector);
	TragetVector = TragetVector.Normalize();
	//TragetVector = TragetVector - (*Speed);

	return TragetVector;
}

CVector2D Boid::flee(CVector2D *StartVector, CVector2D *DangerVector, float RangeOfDanger)
{
	return ((*StartVector) - (*DangerVector)).Normalize() * RangeOfDanger;
}

