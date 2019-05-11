#pragma once
#include <cmath>//!<- for calculating magnitude 
#include <iostream>
class CVector2D
{
public:// constructors 
	CVector2D();
	CVector2D(float x, float y);
	~CVector2D();
public:// functions

	//! multiplying 2 vectors, 2D vector give a scalar.
	float DotProduct(CVector2D &OtherVector);
	// return the theoretical component Z axis 
	float CrossProduct(CVector2D &OtherVector);
	
	/*! creates a new vector */
	CVector2D Add(CVector2D &OtherVector);
	/*! creates a new vector and can be used the tell distance*/
	CVector2D Subtrack(CVector2D &OtherVector);
	/*! crates a new vector */
	CVector2D ScalarMultiplation(float Scalar);
	/*! Give a normal (unit) vector */
	CVector2D Normalize();
	/*! how long a vector is */
	float Magnitude();
	/*! can be used to tell the RELATIVE distance*/
	float SquaredMagnitude();

	float InvserSqaredRoot();

	float Angle();

	float AngleBetweenTwoVectors(CVector2D &OtherVector);

	float GetX() const;
	float GetY() const;

	void SetX(float value);
	void SetY(float value);


	CVector2D operator+(const CVector2D &OtherVector);
	CVector2D	operator-(const CVector2D &OtherVector);
	// the same as DotProduct
	float operator*(const CVector2D &OtherVector);

	/* alters the vector */
	CVector2D operator+= (const CVector2D &OtherVector);
	/*!Return the Current ofter operation vector */
	CVector2D operator-= (const CVector2D &OtherVector);
	/*!alters this vector and returns the result of multiplaction */
	CVector2D operator*= (const CVector2D &OtherVector);
	//!return a new vector 
	CVector2D operator*(const float &Scalar);

	void operator=(const CVector2D &OtherVector);

	float Y;
private://variables 

	float X;

};

