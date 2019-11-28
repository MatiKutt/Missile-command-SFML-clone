//// <summary>
/// @author Mati Kutt
/// @date Nov 2019
///Session 1: created all the game objects
/// Session 2: wasted an hour running in circles
///sesstion 3: got the player firing and explosion mechanics complete
//session 4:basework for enemies complete
/// 
/// you need to change the above lines or lose marks
/// project comment in main.cpp
/// </summary>



#include "MyVector2.h"
#include "Game.h"
#include <iostream>
#include <ctime>
#include <random>
#include <sstream>
#include <iostream>




/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Earth Offense" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	srand(time(nullptr));
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps

		}

		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);

		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseReleaseEvents(newEvent); // keep code tidy			
		}
	}







}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}


	if (GameOver != true && maxPower == false)
	{

		updatePower();

	}







		if (asteroidInPlay == false)
		{
			asteroidSource.x = (rand() % 800);
			asteroidWant.x = (rand() % 600);



			lengthAsteroid = (asteroidWant - asteroidSource);

			m_unitVectorLength2 = vectorUnitVector(lengthAsteroid);

			m_velocityAsteroid = { m_unitVectorLength2 * m_asteroidSpeed };

			m_laserAsteroid.append(asteroidSource);
			asteroidLocation = asteroidSource;

		}

		drawAsteroid();


	if (currentState == gameState::readyToFire)
	{


	}


	if (currentState == gameState::Firing)
	{
		updateMissile();
	}



	if (currentState == gameState::Explosion)
	{
		drawExplosion();
	}

	if (currentState == gameState::explosionExpansion)
	{
		updateExplosion();
	}


	if (GameOver == true)
	{
		currentState = gameState::over;
		m_asteroidSpeed = (20.0f);
	}



	
	


}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{

  

	m_window.clear(sf::Color::Black);
	m_window.draw(m_currentPoints);
	m_window.draw(m_currentLives);
	m_window.draw(m_base);
	m_window.draw(m_ground);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_altitudeBar);
	m_window.draw(m_laser);
	m_window.draw(m_boom);
	m_window.draw(m_laserAsteroid);
	if (GameOver == true)
	{
		m_window.draw(m_GameOver);
	}
	m_window.display();

	
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("Altitude");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(25.0f, 540.0f);
	m_welcomeMessage.setCharacterSize(20U);
	m_welcomeMessage.setFillColor(sf::Color::Black);



	m_altitudeBar.setPosition(140.0f, 540.0f);
	m_base.setFillColor(sf::Color::Red);
	m_base.setPosition(375.0f, 450.0f);
	m_ground.setFillColor(sf::Color::Blue);
	m_ground.setPosition(0.0f, 500.0f);
	m_ground.setSize(sf::Vector2f(800.0f, 150.0f));


	m_GameOver.setFont(m_ArialBlackfont);
	m_GameOver.setString("GAME OVER");
	m_GameOver.setStyle(sf::Text::Underlined | sf::Text::Bold);
	m_GameOver.setPosition(400.0f, 300.0f);
	m_GameOver.setCharacterSize(50U);
	m_GameOver.setFillColor(sf::Color::White);

	m_currentLives.setFont(m_ArialBlackfont);
	m_currentLives.setString("Current lives: " + playerLivesInText);
	m_currentLives.setStyle(sf::Text::Underlined | sf::Text::Bold);
	m_currentLives.setPosition(10.0f,10.0f);
	m_currentLives.setCharacterSize(15U);
	m_currentLives.setFillColor(sf::Color::White);

	m_currentPoints.setFont(m_ArialBlackfont);
	m_currentPoints.setString("Points: " + pointsInText);
	m_currentPoints.setStyle(sf::Text::Underlined | sf::Text::Bold);
	m_currentPoints.setPosition(10.0f, 50.0f);
	m_currentPoints.setCharacterSize(15U);
	m_currentPoints.setFillColor(sf::Color::White);

}


void Game::processMouseReleaseEvents(sf::Event t_mouseEvent)
{
	if (currentState == gameState::readyToFire) {



		m_mouseClick = sf::Vector2f{ static_cast<float>(t_mouseEvent.mouseButton.x),static_cast<float>(t_mouseEvent.mouseButton.y) };
		sf::Vector2f length = (m_mouseClick - m_source);
		m_unitVectorLength = vectorUnitVector(length);
		m_velocity = { m_unitVectorLength * m_LASERSPEED };
		m_missileLocation = m_source;
		currentState = gameState::Firing;
	}
	

}




void Game::drawExplosion()
{



	m_boom.setPosition(m_missileLocation.x - 50.0f, m_missileLocation.y - 50.0f);
	m_boom.setFillColor(sf::Color::Transparent);
	m_boom.setOutlineThickness(1.0f);
	m_boom.setOutlineColor(sf::Color::Yellow);


	currentState = gameState::explosionExpansion;
	maxPower = false;
	currentCharge.x = (0.0f);
	availableHeight.y = (350.0f);
}




/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{

}



void Game::updateMissile()
{

	m_missileLocation += m_velocity;
	m_laser.append(sf::Vertex{ (m_source), sf::Color::Black });
	m_laser.append(sf::Vertex{ sf::Vector2f(m_missileLocation), sf::Color::Red });
	


	if (m_missileLocation.y < m_mouseClick.y || m_missileLocation.y < availableHeight.y)
	{
		m_laser.clear();
		currentState = gameState::Explosion;
		
	}

}


//updates the explosion while radius < max radius
void Game::updateExplosion()
{


	m_explosionCurrentRadius += 1.0f;
	m_boom.setRadius(m_explosionCurrentRadius);
	m_boom.setPosition(m_missileLocation.x - m_explosionCurrentRadius, m_missileLocation.y - m_explosionCurrentRadius);



	sf::Vector2f distanceBetweenProjectiles = asteroidLocation - m_missileLocation;

	if (vectorLengthSquared(distanceBetweenProjectiles) < m_explosionCurrentRadius * m_explosionCurrentRadius)
	{
		m_points++;
		m_laserAsteroid.clear();
		asteroidInPlay = false;
		updatePoints();

	}


	if (m_explosionCurrentRadius > m_explosionMaxRadius)
	{

		m_explosionCurrentRadius = 0.0001f;
		m_boom.setPosition(100000.0f, 100000000.0f);
		currentState = gameState::readyToFire;
	

	}
}



void Game::drawAsteroid()
{




	asteroidInPlay = true;



	asteroidLocation += m_velocityAsteroid;
	asteroidLocation = asteroidLocation;
	
	m_laserAsteroid.append(sf::Vertex{ sf::Vector2f(asteroidSource),sf::Color::Black });
	m_laserAsteroid.append(sf::Vertex{ sf::Vector2f(asteroidLocation),sf::Color::Yellow });



	if (asteroidLocation.y > asteroidWant.y)
	{
		m_laserAsteroid.clear();
		playerLives = (playerLives - 1);
		asteroidInPlay = false;


		if (currentState != gameState::over)
		{
			UpdateLives();
		}


		if (playerLives == 0)
		{
			GameOver = true;
		}

	}

}

void Game::generateOrigin()
{
	asteroidSource.x = rand() % 800;
}


void Game::UpdateLives()
{

	std::stringstream playerLivesToText;
	playerLivesToText << playerLives;
	playerLivesToText >> playerLivesInText;
	m_currentLives.setString("Current lives: " + playerLivesInText);



}

void Game::updatePower()
{
	

	currentCharge += barChargeRate;


	m_altitudeBar.setSize(currentCharge + barChargeRate);

	
	availableHeight.y = (availableHeight.y - heightIncrease);
	


	if (currentCharge.x > 300.0f)
	{
		availableHeight.y = 0.0f;
		maxPower = true;
	}




}


void Game::updatePoints()
{

	std::stringstream pointsToText;
	pointsToText << m_points;
	pointsToText >> pointsInText;
	m_currentPoints.setString("Points: " + pointsInText);
	hiddenLifeGain++;
	if (hiddenLifeGain == 7)
	{
		playerLives++;
		hiddenLifeGain = 0;
		UpdateLives();
	}
}