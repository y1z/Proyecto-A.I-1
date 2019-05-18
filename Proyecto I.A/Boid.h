#pragma once
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
	void Upadate();
	void Render();


	void SetPosition(const CVector2D &Position);
	void SetDirection(const CVector2D &Direction);
	void SetSpeed(float speed);

	float Distance(Boid &OtherBoid);
	float Distance(CVector2D &OtherVector);
	CVector2D GetPosition();//const;
	CVector2D GetDirection() const;
	float GetSpeed();
	/*! returns a vector that tell the boid where to go */
	static CVector2D Seek(CVector2D *StartVector, CVector2D *Speed, CVector2D *OtherPoint);
	/*! returns a vector that tell the boid to run away*/
	static CVector2D flee(CVector2D *StartVector, CVector2D *DangerVector, float RangeOfDanger);
public:// variables 
	CVector2D m_position;
	CVector2D m_direction;
	float m_speed;

};

