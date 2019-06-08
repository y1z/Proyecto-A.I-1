#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Boid.h"
#include "HelperFunctions.h"

enum Behavior
{
	NONE = -1,
	Seek,
	Flee,
	Wander,
};

struct BoidAndBehavoir
{
	Boid boid;
	Behavior behavoir;
};

class BoidManager
{
public:// constructor 
	BoidManager();
	~BoidManager();
public: // functions 
	//! inserts boid to the Sand-box 
	void AddBoid(Boid &newBoid,Behavior behavoir);
	//! make and adds them 
	void CreateAndAddBoid(Behavior behavoir, float speed = 1.0f, float mas = 0.7f, float PosX = 100.0f, float PosY = 100.0f);

	void SetRenderTargetWindow(sf::RenderWindow &Window);
	//! updates every single boid and prepares them to be drawn.
	void  Update();
	//! Presents all the boids in the Sand-box to the Window 
	void Display();
	//! This cleans the screen before 
	void Clear();

	Boid& GetBoid(int Index);
	//! returns a boid that in the Index 
	CVector2D GetBoidPosition(int Index);
	//! returns the vector that contains all the boids 
	std::vector<BoidAndBehavoir>& GetBoidsVector();

private:// variables
	sf::RenderWindow *mptr_Window = nullptr;
	sf::Texture m_GenericBoidTex;
	sf::Sprite m_GenericBoidSprite;
	std::vector<BoidAndBehavoir> m_Boids;
	std::vector<bool> m_ColidingBoids;
};

