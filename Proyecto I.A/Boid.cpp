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

bool Boid::Init(const CVector2D & Position, const CVector2D & Direction, float speed, float Mas)
{
	m_position = Position;
	m_direction = Direction;
	m_speed = speed;
	m_Mas = Mas;

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

void Boid::SetSprite(sf::Sprite & refSprite)
{
	m_sprite = refSprite;
}

float Boid::Distance(Boid & OtherBoid) const
{
	CVector2D DistanceVector = (OtherBoid.m_position - m_position);

	return DistanceVector.SquaredMagnitude();
}

float Boid::Distance(const CVector2D & OtherVector) const
{
	return (OtherVector - m_position).SquaredMagnitude();
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
	// checks distance between the fleer and the "DangerCenter"
	if ((Fleer.GetPosition() - DangerCenter).SquaredMagnitude() < Radius * Radius)
	{
		return Seek(Fleer, DangerCenter) * -1.0f;
	}

	// basically don't move  
	return CVector2D(0.f, 0.f);
}

CVector2D Boid::wander(const Boid &Seeker, float WanderAngle)
{
	CVector2D CirclePosition = (Seeker.GetPosition() + Seeker.GetVelocity()).Normalize() * 10.0f;

	std::random_device rd;
	static std::mt19937 RandGenrator(rd());
	std::uniform_real_distribution<float> Range(-WanderAngle, WanderAngle);

	float AngleX = Range(RandGenrator);
	float AngleY = Range(RandGenrator);

	AngleX += std::cos(Range(RandGenrator));
	AngleY += std::sin(Range(RandGenrator));

	return 	 CVector2D(AngleX, AngleY).Normalize() * 10.5f;
}

CVector2D Boid::Arrive(const Boid & Arriver, const CVector2D & ArrivePosition, float Radius)
{
	CVector2D TargetVector = (ArrivePosition - Arriver.m_position).Normalize();
	CVector2D RaidusVector = ArrivePosition + CVector2D(0.0f, Radius);

	float SqureMagRadius = (RaidusVector - ArrivePosition).SquaredMagnitude();
	float SeekerDistance = Arriver.Distance(ArrivePosition);

	if (SeekerDistance < SqureMagRadius)
	{
		/* Values range from 0 ... 1*/
		float ProporcionalDistance = (SeekerDistance / SqureMagRadius) * 100.0f * 0.01f;
		std::cout << "Proporcional Diatace " << ProporcionalDistance << '\n';

		(ProporcionalDistance < 0.01f) ? TargetVector * 0 : TargetVector = TargetVector * ProporcionalDistance;
	}

	return TargetVector;
}
