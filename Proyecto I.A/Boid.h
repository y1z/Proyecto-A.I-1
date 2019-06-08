#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "CVector2D.h"
#include "HelperFunctions.h"

/*!
\brief this class will be used for simple A.I behavior
*/

class Boid
{
public:// constructor
	Boid();
	~Boid();
public:// functions
	bool Init(const CVector2D &Position, const CVector2D &Direction, float speed, float mas);
	void Destroy();
	void Upadate(sf::RenderWindow &Windows);
	void Render(sf::RenderWindow &Windows);

	void SetPosition(const CVector2D &Position);
	void SetDirection(const CVector2D &Direction);
	void SetVelocity(float x, float y);
	void SetSpeed(float speed);
	void SetSprite(sf::Texture & TextureForSprite, float ScaleX = 1.0f, float ScaleY = 1.0f);
	void SetSprite(sf::Sprite &refSprite);
	/*! this function uses squared magnitude to determine distance*/
	float Distance(Boid &OtherBoid);
	/*! this function uses squared magnitude to determine distance*/
	float Distance(CVector2D &OtherVector);

	CVector2D GetPosition() const;
	CVector2D GetDirection();
	CVector2D GetVelocity() const;
	CVector2D GetDirection() const ;
	float GetSpeed() const;

	/*! returns a vector that tell the boid where to go */
	static CVector2D Seek(const Boid &Seeker, const CVector2D& OtherPoint);
	/*! returns a vector that tell the boid to run away*/
	static CVector2D flee(const Boid &Fleer, const CVector2D& DangerCenter, float Radius);
	/*! Expect's a angle in degrees*/
	static CVector2D wander(const Boid &Seeker, float WonderAngle);
	/*! Give a vector that will decrement every time the seeker get closer */
	static CVector2D Arrive(const Boid &Seeker, const Boid &Target);

public:// variables 
	CVector2D m_position;
	CVector2D m_Velocity;
	CVector2D m_direction;

	float m_Mas = 0.9f;
	float m_SteerForce = 150.f;
	float m_speed;
private:
	sf::Sprite m_sprite;
};

