#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "CVector2D.h"
#include "Boid.h"
#include "HelperFunctions.h"
#include "SandBox.h"
#include "BoidManager.h"
#include "BoidDemos.h"

void BoidsRacing(BoidManager &RaceTrack);

void Start();

int main()
{
	Start();
}

/*! Begins the program */
void Start()
{
	Boid Seeker;
	Seeker.Init(CVector2D(0, 0), CVector2D(-20, -5), 1);

	Boid Traget;
	Traget.Init(CVector2D(1000, 110), CVector2D(0, 0), 1);

	sf::Texture TexSeeker;
	sf::Texture TexTraget;
	// Use "/" Or nothings loads 
	TexSeeker.loadFromFile("images/S_Seeker.png");
	TexTraget.loadFromFile("images/S_Traget.png");

	Seeker.SetSprite(TexSeeker);
	Traget.SetSprite(TexTraget);

	Seeker.SetVelocity(-200.0f, 200.0f);

	BoidManager BoidManager;
	BoidManager.AddBoid(Seeker, Behavior::Seek);
	BoidManager.AddBoid(Traget, Behavior::Seek);

	Seeker.SetSpeed(200.f);
	BoidsRacing(BoidManager);
	//BoidsArriveDemo(Seeker, Traget, 5);
	//BoidsFleeDemo(Seeker, Traget, 75);
	//BoidsSeekDemo(Seeker, Traget);
	//BoidsWonderRadiusDemo(Seeker);
	//BoidsWonderTimeDemo(Seeker);
}


void BoidsRacing(BoidManager & BoidsGroup)
{
	//Tracks the mouse Position 
	CVector2D CurrentMousePosition;
	CurrentMousePosition.SetX(1500.f);
	CurrentMousePosition.SetY(0.0f);

	sf::Time passedTime(sf::seconds(0.01f));
	sf::Clock clock;
	sf::RenderWindow Window(sf::VideoMode(3000, 1200), "Boid Seeker Demo", sf::Style::Default);
	sf::Event MY_Event;

	BoidsGroup.SetRenderTargetWindow(Window);

	bool IsWindowRunnig = true;
	while (IsWindowRunnig)
	{
		// give every boid it's behavior
		for (int i = 0; i < BoidsGroup.GetBoidsVector().size(); ++i)
		{
			if (BoidsGroup.GetBoidsVector()[i].behavoir == Behavior::Seek)
			{
				CVector2D TargetVector = Boid::Seek(BoidsGroup.GetBoid(i), CurrentMousePosition);
				BoidsGroup.GetBoid(i).m_Velocity = (BoidsGroup.GetBoid(i).m_Velocity + TargetVector).Normalize() * 100.f;
				BoidsGroup.GetBoid(i).m_position += (BoidsGroup.GetBoid(i).m_Velocity) * passedTime.asSeconds();
			}

		}

		WindowEvents(Window, IsWindowRunnig, CurrentMousePosition);

		passedTime = clock.restart();

		BoidsGroup.Clear();
		BoidsGroup.Update();
		BoidsGroup.Display();
	}

}

