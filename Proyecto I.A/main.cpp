#include <iostream>
#include "CVector2D.h"

#include "Boid.h"
#include "HelperFunctions.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
void BoidsSeek(Boid &Seeker, Boid &Target);
void BoidsFlee(Boid &Seeker, Boid &Target, float RangeOfDanger);

bool Start();

int main()
{

	//Start();
	//CVector2D Start(0, 0);
	//CVector2D Endpoint(4, 4);
	//float DangerRange = 5;

	Boid Seeker;
	Seeker.Init(CVector2D(10, 1), CVector2D(-5, -5), 1);

	Boid Traget;
	Traget.Init(CVector2D(5, 5), CVector2D(0, 0), 1);

	//BoidsFlee(Seeker, Traget, 0.9f);
	//BoidsSeek(Seeker, Traget);
	BoidsSeek(Seeker, Traget);
	DumbStop();
}
/*! this function is just to test the seek behavior*/
void BoidsSeek(Boid & Seeker, Boid &TargetBoid)
{
	sf::RenderWindow Window(sf::VideoMode(600, 600), "Boid Seeker visualizer", sf::Style::Default);

	sf::Texture TexSeeker;
	sf::Texture TexTraget;
	// Use "/" Or nothings loads 
	TexSeeker.loadFromFile("images/S_Seeker.png");
	TexTraget.loadFromFile("images/S_Traget.png");

	sf::Sprite spriteSeeker(TexSeeker);
	sf::Sprite spriteTraget(TexTraget);

	spriteTraget.setPosition(TargetBoid.m_position.GetX(), TargetBoid.m_position.GetY());
	while (true)
	{
		//CVector2D TragetVector;// = Boid::Seek(&Seeker.GetPosition(), &Seeker.GetDirection(), &TargetBoid.GetPosition());
	//	CVector2D ChangeInForce =	Seeker.Seek(&Seeker.GetPosition(), &Seeker.GetDirection(), &TargetBoid.GetPosition());
		CVector2D ChangeInForce;
		CVector2D TragetVector = (TargetBoid.m_position - Seeker.m_position) * 1.25f;

		/*! used to make boid not go to far away from target*/
		ChangeInForce += TragetVector.Normalize();

	//	ChangeInForce = (TargetBoid.m_position - Seeker.m_position).Normalize() * 1.25f;

		Seeker.m_position += ChangeInForce;
		
		spriteSeeker.setPosition(Seeker.m_position.GetX(), Seeker.m_position.GetY());

		std::cout << "Current Position " << Seeker.m_position << "\n";

		Window.draw(spriteTraget);
		Window.draw(spriteSeeker);
		Window.display();
	//	DumbStop();
	}

}

void BoidsFlee(Boid & Seeker, Boid &DangerBoid, float DangerRange)
{
	while (true)
	{
		CVector2D TragetVector = Seeker.flee(&Seeker.GetPosition(), &Seeker.GetDirection(), DangerRange);

		CVector2D ChangeInForce;

		if (DangerBoid.Distance(Seeker) > TragetVector.SquaredMagnitude())
		{
			std::cout << "WHAT'S UP DANGER \n";
			 ChangeInForce = ((TragetVector - Seeker.m_position).Normalize() * 1.25f) * -3;
		}
		else
		{
			 ChangeInForce = (TragetVector - Seeker.m_position).Normalize() * 1.25f;

		}
		Seeker.m_position += ChangeInForce;


		std::cout << "Current Position " << Seeker.m_position << "\n";

		DumbStop();
	}
}
/*! Begins the program */
bool Start()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(1280, 720), "Ventana Meca",
		sf::Style::Default);

	sf::Texture texture;
	if (!texture.loadFromFile("images/S_scribble.png"))
		return EXIT_FAILURE;

	sf::Sprite sprite(texture);

	sprite.scale(0.1f, 0.1f);

	CVector2D test(3, 3);

	sprite.setOrigin(test.GetX(), test.GetY());

	while (true)
	{
		Window.draw(sprite);
		Window.display();
	}

	return false;
}
