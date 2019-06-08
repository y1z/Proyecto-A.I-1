#include "BoidManager.h"

BoidManager::BoidManager()
{
	m_GenericBoidTex.loadFromFile("images/S_Seeker.png");
	m_GenericBoidSprite.setTexture(m_GenericBoidTex);
}

BoidManager::~BoidManager()
{}

void BoidManager::AddBoid(Boid &newBoid, Behavior behavoir)
{
	BoidAndBehavoir IngresedBoid;
	IngresedBoid.boid = newBoid;
	IngresedBoid.behavoir = behavoir;

	m_Boids.emplace_back(IngresedBoid);
}

void BoidManager::CreateAndAddBoid(Behavior behavoir, float speed, float mas,float PosX, float PosY)
{
	BoidAndBehavoir NewBoid;
	NewBoid.boid.Init(CVector2D(PosX, PosY), CVector2D(-1.0f, -1.0f), speed, mas);
	NewBoid.behavoir = behavoir;

	NewBoid.boid.SetSprite(m_GenericBoidSprite);

	m_Boids.emplace_back(NewBoid);
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

