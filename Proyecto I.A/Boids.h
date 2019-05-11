#pragma once
#include "CVector2D.h"
#include "HelperFunctions.h"
class Boids
{
public:// constructor
	Boids();
	~Boids();
public:// functions
	bool Init();
	void Destroy();
	void Upadate();
	void Render();

	void SetPosition(float x, float y);

	static void Seek(CVector2D &OtherPoint);
	static void flee();
public:// variables 
	CVector2D m_position;
	CVector2D m_direction;
	float m_speed;

};

