#include <iostream>
#include "CVector2D.h"
#include "Boid.h"
#include "HelperFunctions.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
/*! this function is just to test the seek behavior*/
void BoidsSeekDemo(Boid &Seeker, Boid &Target);
/*! this function is just to test the flee behavior*/
void BoidsFleeDemo(Boid &FleeBoid, Boid &Target, float RangeOfDanger);
void BoidsWonderDemo(Boid &WonderBoid);
bool Start();

int main()
{
	Start();
	// just for debugging
	DumbStop();
}

void BoidsSeekDemo(Boid & Seeker, Boid &TargetBoid)
{
	sf::RenderWindow Window(sf::VideoMode(600, 600), "Boid Seeker visualizer", sf::Style::Default);
	while (true)
	{
		CVector2D TragetVector = Boid::Seek(&Seeker.GetPosition(), &Seeker.GetDirection(), &TargetBoid.GetPosition());

		/*To control the speed of movement*/
		CVector2D ChangeInForce = TragetVector * Seeker.m_speed;

		Seeker.m_direction += ChangeInForce;

		Seeker.m_position += Seeker.m_direction;
		/*To change the current positions on screen*/
		TargetBoid.Upadate(Window);
		Seeker.Upadate(Window);

		Window.display();
		Window.clear();
		std::cout << "Current Position " << Seeker.m_position << "\n";
	}

}

void BoidsFleeDemo(Boid & Seeker, Boid &DangerBoid, float DangerRange)
{
	sf::RenderWindow Window(sf::VideoMode(600, 600), "Boid Flee Demo", sf::Style::Default);

	if (Seeker.GetPosition() == DangerBoid.GetPosition())
	{
		// Stop error when calculating ditance	
		Seeker.m_position += CVector2D(2, 2);
	}

	while (true)
	{
		CVector2D RunAwayVector = Boid::flee(&Seeker.GetPosition(), &Seeker.GetDirection(), DangerRange);

		CVector2D ChangeInForce(0, 0);

		if (DangerBoid.Distance(Seeker) < (RunAwayVector.SquaredMagnitude()))
		{
			std::cout << "WHAT'S UP DANGER \n";

			ChangeInForce += ((RunAwayVector - Seeker.m_position).Normalize() *  +DangerRange);
		}

		ChangeInForce += (DangerBoid.m_position - Seeker.m_position).Normalize();

		Seeker.m_direction += ChangeInForce;
		Seeker.m_position += Seeker.m_direction;

		Seeker.Upadate(Window);
		DangerBoid.Upadate(Window);


		std::cout << "Current Position " << Seeker.m_position << "\n";

		Window.display();
		Window.clear();
		DumbStop();
	}
}

void BoidsWonderDemo(Boid & WonderBoid)
{
	sf::RenderWindow Window(sf::VideoMode(1280, 1280), "Boid Wonder demo", sf::Style::Default);

	CVector2D WonderVector = Boid::wonder(700, 700);

	srand(time(0));

	std::cout << "First Wonder Vector " << WonderVector << '\n';
	while (true)
	{
		CVector2D ChangeInForce = Boid::Seek(&WonderBoid.m_position, &WonderBoid.m_direction, &WonderVector);
		
		WonderBoid.m_direction += (ChangeInForce * WonderBoid.m_speed);
		WonderBoid.m_position += WonderBoid.m_direction;

		WonderBoid.Upadate(Window);

		if(WonderBoid.Distance(WonderVector) < 55000.0f)
		{
			WonderVector = Boid::wonder(600, 400);
			WonderVector += (WonderBoid.m_direction * -1);
			std::cout << "new Wonder Position : "<< WonderVector<<"\n";
		}

		std::cout << WonderBoid.m_position<<'\n';
		
		Window.display();
		Window.clear();
	}

}
/*! Begins the program */
bool Start()
{
	Boid Seeker;
	Seeker.Init(CVector2D(200, 200), CVector2D(-20, -5), 1);

	Boid Traget;
	Traget.Init(CVector2D(200, 200), CVector2D(0, 0), 1);

	sf::Texture TexSeeker;
	sf::Texture TexTraget;
	// Use "/" Or nothings loads 
	TexSeeker.loadFromFile("images/S_Seeker.png");
	TexTraget.loadFromFile("images/S_Traget.png");

	Seeker.SetSprite(TexSeeker);
	Traget.SetSprite(TexTraget);

	//BoidsFleeDemo(Seeker, Traget, 20.0f);
	//BoidsSeekDemo(Seeker, Traget);
	BoidsWonderDemo(Seeker);

	return false;
}
