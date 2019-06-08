#include "BoidManager.h"

BoidManager::BoidManager()
{}

BoidManager::~BoidManager()
{}

void BoidManager::AddBoid(Boid &newBoid, Behavior behavoir)
{
	BoidAndBehavoir IngresedBoid;
	IngresedBoid.boid = newBoid;
	IngresedBoid.behavoir = behavoir;

	m_Boids.emplace_back(IngresedBoid);
}

void BoidManager::SetRenderTargetWindow(sf::RenderWindow & Window)
{
	mptr_Window = &Window;
}

void BoidManager::Update()
{
	for (auto CurrentBoid : m_Boids) 
	{
		CurrentBoid.boid.Upadate(*mptr_Window);
	}
}

void BoidManager::Display()
{
	mptr_Window->display();
}

void BoidManager::Clear()
{
	mptr_Window->clear();
}

Boid & BoidManager::GetBoid(int Index)
{
	if (isWithinVectorBounds(Index, m_Boids))
	{
		return m_Boids[Index].boid;
	}
}

CVector2D BoidManager::GetBoidPosition(int Index)
{
	if (isWithinVectorBounds(Index, m_Boids))
	{
		return m_Boids[Index].boid.GetPosition();
	}

	return CVector2D(-1337, -1337);
}

std::vector<BoidAndBehavoir>& BoidManager::GetBoidsVector()
{
	return m_Boids;
}

