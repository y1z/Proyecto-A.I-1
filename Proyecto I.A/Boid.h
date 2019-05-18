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
	bool Init(const CVector2D &Position, const CVector2D &Direction, float speed);
	void Destroy();
	void Upadate(sf::RenderWindow &Windows);
	void Render(sf::RenderWindow &Windows);


	void SetPosition(const CVector2D &Position);
	void SetDirection(const CVector2D &Direction);
	void SetSpeed(float speed);
	void SetSprite(sf::Texture & TextureForSprite, float ScaleX = 1.0f, float ScaleY = 1.0f);
	/*! this function uses squared magnitude to determine distance*/
	float Distance(Boid &OtherBoid);

	float Distance(CVector2D &OtherVector);
	CVector2D GetPosition();
	CVector2D GetDirection() const;
	float GetSpeed();
	/*! returns a vector that tell the boid where to go */
	static CVector2D Seek(CVector2D *StartVector, CVector2D *Speed, CVector2D *OtherPoint);
	/*! returns a vector that tell the boid to run away*/
	static CVector2D flee(CVector2D *StartVector, CVector2D *DangerVector, float RangeOfDanger);
	/*! reruns a vector that's placed between a range randomly*/
	static CVector2D wonder(int MinX, int MaxX, int MinY = 1, int MaxY = 1);

public:// variables 
	CVector2D m_position;
	CVector2D m_direction;
	float m_speed;
private:
	sf::Sprite m_sprite;

};

