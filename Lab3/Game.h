/// <summary>
/// author Mati Kutt Nov 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// 
/// project comment in main.cpp
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void Game::processMouseReleaseEvents(sf::Event t_mouseEvent);
	void setupFontAndText();
	void setupSprite();
	void drawExplosion();
	void Game::updateMissile();
	void Game::updateExplosion();
	void Game::drawAsteroid();
	void Game::generateOrigin();
	void Game::UpdateLives();
	void Game::updatePoints();

	void Game::updatePower();


	enum class gameState
	{
		readyToFire, Firing, Explosion, explosionExpansion, over
	};

	gameState currentState = gameState::readyToFire;


	bool GameOver{ false };
	bool maxPower{ false };
	bool asteroidInPlay{ false };

	sf::Vector2f m_lineVelocity { 0.0f, 0.0f };

	const float m_LASERSPEED{ 6.5f };

	float m_explosionMaxRadius{ 40.0f };
	float m_explosionCurrentRadius{ 0.001f };
	float m_asteroidSpeed{ 2.5f };







	sf::CircleShape m_boom; // circle shape for explosion

	sf::Vector2f m_unitVectorLength; // used to store unit vector length




	sf::RectangleShape m_base{ (sf::Vector2f(50.0f, 50.0f)) }; // base, source of shots
	sf::RectangleShape m_ground; // ground shape
	sf::RectangleShape m_altitudeBar{ (sf::Vector2f(0.0f,25.0f)) }; // fire distance bar


	sf::Vector2f barChargeRate{ 2.0f,0.0f };
	sf::Vector2f currentCharge{ 0.0f,25.0f };


	sf::Vector2f availableHeight{ 0.0f,0.0f };
	float heightIncrease{ 1.10f };


	sf::Vector2f m_missileLocation{ 0.0f,0.0f }; // current location of missile
	sf::Vector2f m_destination = sf::Vector2f{ 0.0f,0.0f }; // intended location of missile, mousclick
	sf::Vector2f m_velocity{ 0.0f,0.0f }; // velocity of missile
	


	///test values for asteroid
	/// 
	/// 
	/// 
	sf::Vector2f m_velocityAsteroid{ 0.0f,0.0f };
	sf::Vector2f asteroidSource{ 400.0f, 0.0f };


	sf::Vector2f asteroidLocation{ 0.0f, 0.0f };
	sf::Vector2f asteroidWant{ 400.0f, 500.0f };
	sf::Vector2f lengthAsteroid = { 0.0f,0.0f };
	sf::Vector2f m_unitVectorLength2 = { 0.0f,0.0f };



	int m_points{ 0 };
	std::string pointsInText{ "0" };

	int playerLives{ 3 };
	std::string playerLivesInText{ "3"};
	int hiddenLifeGain{ 0 };





	sf::Vector2f m_mouseClick{ 0.0f,0.0f };


	const sf::Vector2f m_source{ sf::Vector2f(400.0f, 500.0f) };
	sf::Vector2f m_endPoint{ sf::Vector2f(0.0f,0.0f) };




	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Text m_GameOver;
	sf::Text m_currentLives;
	sf::Text m_currentPoints;


	sf::VertexArray m_laser{ sf::Lines };
	sf::VertexArray m_laserAsteroid{ sf::Lines };
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP