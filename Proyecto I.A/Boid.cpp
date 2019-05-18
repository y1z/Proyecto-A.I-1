#include "Boid.h"
#include "HelperFunctions.h"
#include <random>
#include <ctime>// used for random function

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
	return TragetVector;
}

CVector2D Boid::flee(CVector2D *StartVector, CVector2D *DangerVector, float RangeOfDanger)
{
	return ((*StartVector) - (*DangerVector)).Normalize() * RangeOfDanger;
}

CVector2D Boid::wonder(int MinX, int MaxX, int MinY, int MaxY)
{

	int PosX = (rand() % MaxX);
	int PosY = (rand() % MaxY);

	return CVector2D(PosX, PosY);
}

