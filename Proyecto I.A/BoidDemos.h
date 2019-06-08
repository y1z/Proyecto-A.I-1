#pragma once
#include "CVector2D.h"
#include "Boid.h"
#include "HelperFunctions.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*! this function is just to test the seek behavior*/
void BoidsSeekDemo(Boid &Seeker, Boid &Target);
/*! this function is just to test the flee behavior*/
void BoidsFleeDemo(Boid &FleeBoid, Boid &Target, float RangeOfDanger);
/*! Move the Boid to a range of random positions */
void BoidsWanderRandomPositionDemo(Boid &WanderBoid);

void BoidsWanderRadiusDemo(Boid &WonderBoid);

void BoidsArriveDemo(Boid &Seeker, Boid &Traget, float Radius);


void BoidsSeekDemo(Boid & Seeker, Boid &TargetBoid)
{
	bool isWindowRuning = true;
	sf::Event MY_Event;
	sf::RenderWindow Window(sf::VideoMode(3000, 1200), "Boid Seeker Demo", sf::Style::Default);
	// measuring time 
	sf::Time TimePassed;
	sf::Clock clock;

	Seeker.SetPosition(CVector2D(3000 / 2, 1200 / 2));

	while (isWindowRuning)
	{
		CVector2D TragetVector = Boid::Seek(Seeker, TargetBoid.GetPosition());

		//Seeker.m_Velocity = (Seeker.m_Velocity + TragetVector).Normalize() * Seeker.m_speed;

		//Seeker.m_position += Seeker.m_Velocity * TimePassed.asSeconds();

		while (Window.pollEvent(MY_Event))
		{
			switch (MY_Event.type)
			{
			case(sf::Event::MouseMoved):
				TragetVector = Boid::Seek(Seeker, TargetBoid.GetPosition());
				TargetBoid.m_position.SetX(MY_Event.mouseMove.x);
				TargetBoid.m_position.SetY(MY_Event.mouseMove.y);
				break;
			case(sf::Event::KeyPressed):
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					Seeker.m_speed += 20.0f;

				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					Seeker.m_speed -= 20;
				}

				break;
			}

		}
		Seeker.m_direction.SetX(1);
		Seeker.m_direction.SetY(0);
		TargetBoid.m_direction.SetX(-0.5f);
		TargetBoid.m_direction.SetY(-0.5f);

		CVector2D PosNorm = TargetBoid.m_direction.Normalize();
		CVector2D PosNormSekr = Seeker.m_direction.Normalize();

		std::cout << " Here is the Dot Product [" << PosNormSekr.DotProduct(PosNorm)<< "] \n";

		/*To change the current positions on screen*/
		TargetBoid.Upadate(Window);
		Seeker.Upadate(Window);

		Window.display();
		Window.clear();

		TimePassed = clock.restart();
	}

}

void BoidsFleeDemo(Boid & Seeker, Boid &DangerBoid, float DangerRange)
{
	sf::RenderWindow Window(sf::VideoMode(1280, 1280), "Boid Flee Demo", sf::Style::Default);
	sf::Event mouseEvents;
	bool isWindowRuning = true;

	if (Seeker.GetPosition() == DangerBoid.GetPosition())
	{
		// Stop error when calculating ditance	
		Seeker.m_position += CVector2D(2, 2);
	}

	while (isWindowRuning)
	{
		CVector2D RunAwayVector = Boid::flee(Seeker, DangerBoid.GetPosition(), DangerRange);

		if (Seeker.m_Velocity.Magnitude() > 300.f)
		{
			Seeker.m_Velocity = Seeker.m_Velocity.Normalize() * 100.0f;
		}

		WindowEvents(Window, isWindowRuning);

		if (Window.pollEvent(mouseEvents))
		{
			if (sf::Event::MouseMoved)
			{
				DangerBoid.m_position.SetX(mouseEvents.mouseMove.x);
				DangerBoid.m_position.SetY(mouseEvents.mouseMove.y);
			}

		}

		Seeker.m_position += Seeker.m_Velocity;

		Seeker.Upadate(Window);
		DangerBoid.Upadate(Window);

		std::cout << "Current Position " << Seeker.m_position << "\n";

		Window.display();
		Window.clear();
		//	DumbStop();
	}
}

void BoidsWanderRandomPositionDemo(Boid & WonderBoid)
{
	sf::RenderWindow Window(sf::VideoMode(1600, 1500), "Boid Wonder demo", sf::Style::Default);
	bool IsWindowRuning = true;
	CVector2D WonderTarget = RandomPos(1600, 1500);

	sf::Time passedTime;
	sf::Clock clock;

	WonderBoid.m_position = CVector2D(700, 100);
	// start loop 
	while (IsWindowRuning)
	{
		CVector2D TargetVector = Boid::Seek(WonderBoid, WonderTarget);

		WonderBoid.m_Velocity = (WonderBoid.m_Velocity + TargetVector).Normalize() * WonderBoid.m_speed;

		WonderBoid.m_position += WonderBoid.m_Velocity * passedTime.asSeconds();

		if (WonderBoid.Distance(WonderTarget) < 100)
		{
			WonderTarget = RandomPos(1600, 1500);
			std::cout << "New Wonder Vector : " << WonderTarget << '\n';
		}

		passedTime = clock.restart();

		WindowEvents(Window, IsWindowRuning);

		WonderBoid.Upadate(Window);
		Window.display();
		Window.clear();
	}
}

void BoidsWanderRadiusDemo(Boid & WonderBoid)
{
	sf::RenderWindow Window(sf::VideoMode(1600, 1500), "Boid Wonder radius demo", sf::Style::Default);

	bool IsWindowRuning = true;

	sf::Time passedTime;

	sf::Clock clock;

	WonderBoid.SetPosition(CVector2D(800, 750));

	CVector2D TargetPosition = RandomPos(1600, 1500);
	// start loop 
	while (IsWindowRuning)
	{
		CVector2D TargetVector = Boid::Seek(WonderBoid, TargetPosition);

		CVector2D WonderVector = Boid::wander(WonderBoid, 70);

		WonderBoid.m_Velocity = (WonderBoid.m_Velocity + WonderVector + TargetVector).Normalize() * WonderBoid.m_speed;

		//	WonderBoid.m_Velocity += WonderVector.Normalize() * WonderBoid.m_speed;

		WonderBoid.m_position += WonderBoid.m_Velocity * 0.01f;

		if (WonderBoid.Distance(TargetPosition) < 100)
		{
			TargetPosition = RandomPos(1600, 1500);
			std::cout << "New Wonder Vector : " << TargetPosition << '\n';
		}

		std::cout << WonderBoid.m_position << '\n';

		WindowEvents(Window, IsWindowRuning);

		WonderBoid.Upadate(Window);
		Window.display();
		Window.clear();
		passedTime = clock.restart();
	}

}

void BoidsArriveDemo(Boid &Seeker, Boid &Traget, float Radius)
{
	bool isWindowRuning = true;
	sf::Event MY_Event;
	sf::RenderWindow Window(sf::VideoMode(3000, 1200), "Boid Seeker Demo", sf::Style::Default);
	// measuring time 
	sf::Time TimePassed;
	sf::Clock clock;

	while (isWindowRuning)
	{
		CVector2D TragetVector = Boid::Arrive(Seeker, Traget.GetPosition(),100);

		Seeker.m_Velocity = TragetVector.Normalize() * Seeker.m_speed;

		Seeker.m_position += Seeker.m_Velocity * TimePassed.asSeconds();

		WindowEvents(Window, isWindowRuning);

		while (Window.pollEvent(MY_Event))
		{
			switch (MY_Event.type)
			{
			case(sf::Event::MouseMoved):
				Traget.m_position.SetX(MY_Event.mouseMove.x);
				Traget.m_position.SetY(MY_Event.mouseMove.y);
				break;
			}

		}

		/*To change the current positions on screen*/
		Traget.Upadate(Window);
		Seeker.Upadate(Window);

		Window.display();
		Window.clear();

		TimePassed = clock.restart();
	}

}
