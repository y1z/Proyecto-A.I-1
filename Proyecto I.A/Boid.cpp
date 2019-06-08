#include "Boid.h"
#include <random>
#include <algorithm>
#include <array>
#include <ctime>// used for random function
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
{}

bool Boid::Init(const CVector2D & Position, const CVector2D & Direction, float speed)
{
	m_position = Position;
	m_direction = Direction;
	m_speed = speed;

	return true;
}

void Boid::Destroy()
{

}

void Boid::Upadate(sf::RenderWindow & Windows)
{
	m_sprite.setPosition(m_position.GetX(), m_position.GetY());
	Windows.draw(this->m_sprite);
}

void Boid::Render(sf::RenderWindow & Windows)
{
	Windows.display();
}

void Boid::SetPosition(const CVector2D & Position)
{
	m_position = Position;
}

void Boid::SetDirection(const CVector2D & Direction)
{
	m_direction = Direction;
}

void Boid::SetVelocity(float x, float y)
{
	m_Velocity.SetX(x);
	m_Velocity.SetY(y);
}

void Boid::SetSpeed(float speed)
{
	m_speed = speed;
}

void Boid::SetSprite(sf::Texture & TextureForSprite, float ScaleX, float ScaleY)
{
	m_sprite.setTexture(TextureForSprite);
	m_sprite.setScale(ScaleX, ScaleY);
}

float Boid::Distance(Boid & OtherBoid)
{
	CVector2D DistanceVector = (OtherBoid.m_position - m_position);

	return DistanceVector.SquaredMagnitude();
}

float Boid::Distance(CVector2D & OtherVector)
{
	return (OtherVector - this->m_position).SquaredMagnitude();
}

CVector2D Boid::GetPosition() const
{
	return m_position;
}

CVector2D Boid::GetDirection() const
{
	return m_direction;
}

CVector2D Boid::GetVelocity() const
{
	return m_Velocity;
}

CVector2D Boid::GetDirection()
{
	CVector2D OtherVector = m_Velocity.Normalize();
	return m_Velocity.Normalize();
}

float Boid::GetSpeed() const
{
	return m_speed;
}

CVector2D Boid::Seek(const Boid &Seeker, const CVector2D& EndPoint)
{
	CVector2D TragetVector = (EndPoint - Seeker.GetPosition());
	CVector2D SteeringVector = (TragetVector - Seeker.m_Velocity).Normalize() * Seeker.m_Mas;

	return SteeringVector;
}

CVector2D Boid::flee(const Boid &Fleer, const CVector2D& DangerCenter, float Radius)
{
	//	CVector2D FleeVector = Seek(Fleer, DangerCenter) * -1;
		//! to check if the boid is in range of Radius 
	CVector2D RadiusVector(DangerCenter + CVector2D(0, Radius));

	if ((Fleer.GetPosition() - RadiusVector).SquaredMagnitude() > Radius * Radius)
	{

	}

	// basically don't move  
	return Fleer.GetPosition();
}

CVector2D Boid::wander(const Boid &Seeker, float WonderAngle)
{
	CVector2D CirclePosition = Seeker.GetPosition() + (Seeker.GetVelocity()).Normalize() * 10.0f;

	static std::default_random_engine RandEngine;

	float AngleX = std::cos(CirclePosition.GetX());
	float AngleY = std::sin(CirclePosition.GetY());
	AngleX += RandEngine() % static_cast<int>(WonderAngle);
	AngleY -= RandEngine() % static_cast<int>(WonderAngle);
	CVector2D WanderForce = CirclePosition + (CVector2D(AngleX, AngleY));

	return 	WanderForce.Normalize() * 10;
}

CVector2D Boid::Arrive(const Boid & Seeker, const Boid & Target)
{
	CVector2D TargetVector = (Target.m_position - Seeker.m_position);

	return TargetVector;
}

