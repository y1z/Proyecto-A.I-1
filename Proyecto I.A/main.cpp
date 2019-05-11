#include <iostream>
#include "CVector2D.h"
#include "Boids.h"



int main() {
	CVector2D Start(0, 0);
	CVector2D Endpoint(4, 4);
	float DangerRange = 5;

	//Boids::Seek(Start, Endpoint);

	Boids::flee(Start, Endpoint, DangerRange);

	DumbStop();
}

