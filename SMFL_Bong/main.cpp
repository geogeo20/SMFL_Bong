#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>


int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	const float pi = 3.14159f;
	const int gameWidth = 800;
	const int gameHeight = 600;
	sf::Vector2f platSize(100, 25);
	float ballRadius = 10.0f;
	int blocksAmmount = 10;


	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "PONG", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	sf::SoundBuffer ballSoundBuffer;
	if (!ballSoundBuffer.loadFromFile("resources/ball.wav"))
		return EXIT_FAILURE;
	sf::Sound ballSound(ballSoundBuffer);

	sf::RectangleShape platform;
	platform.setSize(platSize - sf::Vector2f(3, 3));
	platform.setOutlineThickness(3);
	platform.setOutlineColor(sf::Color::Black);
	platform.setFillColor(sf::Color::Blue);
	platform.setOrigin(platSize / 2.f);
	platform.setPosition(gameWidth / 2, gameHeight - platSize.y);


	sf::CircleShape ball;
	ball.setRadius(ballRadius-3);
	ball.setOutlineThickness(3);
	ball.setOutlineColor(sf::Color::White);
	ball.setFillColor(sf::Color::Black);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	ball.setPosition(gameWidth / 2, gameHeight / 2);

	std::vector <sf::RectangleShape> blocks(blocksAmmount);

	for (size_t i = 0; i < blocksAmmount; i++)
	{
		
		blocks[i] = platform;
		blocks[i].setFillColor(sf::Color::Yellow);
		blocks[i].setPosition(ball.getPosition().x +platSize.x*i, platSize.y);
	}




	sf::Font font;
	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;

	sf::Clock AllTimer;
	

	const float ballSpeed = 400.f;
	float ballAngle = pi / 4;


	sf::Clock clock;
	const float platSpeed = 400.f;

	bool isPlaying = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float deltaTime = clock.restart().asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (platform.getPosition().x - platSize.x / 2) > 5.f)
		{
			platform.move(-platSpeed * deltaTime, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (platform.getPosition().x + platSize.x / 2) < gameWidth - 5.f)
		{
			platform.move(platSpeed * deltaTime, 0.f);
		}

		// Move the ball

		float factor = ballSpeed * deltaTime;
		ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);

		if (ball.getPosition().x - ballRadius < 0.f)
		{
			ballSound.play();
			ballAngle = pi - ballAngle;
			ball.setPosition(ballRadius + 0.01f, ball.getPosition().y);
		}
		if (ball.getPosition().x + ballRadius > gameWidth)
		{
			ballSound.play();
			ballAngle = pi - ballAngle;
			ball.setPosition(gameWidth - ballRadius - 0.01f , ball.getPosition().y);
		}
		if (ball.getPosition().y - ballRadius < 0.f)
		{
			ballSound.play();
			ballAngle = -ballAngle;
			//ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
			ball.setPosition(ball.getPosition().x, ballRadius + 0.01f);
		}
		if (ball.getPosition().y + ballRadius > gameHeight)
		{
			ballSound.play();
			ballAngle = -ballAngle;
			//ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
			ball.setPosition(ball.getPosition().x, gameHeight - ballRadius - 0.01f);
		}
		
		if (ball.getPosition().x + ballRadius >= platform.getPosition().x - platSize.x /2 &&
			ball.getPosition().x - ballRadius <= platform.getPosition().x + platSize.x / 2 &&
			ball.getPosition().y + ballRadius >= platform.getPosition().y - platSize.y / 2 &&
			ball.getPosition().y - ballRadius <= platform.getPosition().y + platSize.y / 2)
		{
			
				ballAngle =- ballAngle - (std::rand() % 20) * pi / 180;
				ballSound.play();
				ball.setPosition(ball.getPosition().x, platform.getPosition().y - ballRadius - platSize.y / 2 + 0.1f );
			
				


		}








		window.clear();
		window.draw(platform);
		for (size_t i = 0; i < blocksAmmount; i++)
		{
			window.draw(blocks[i]);
		}
		window.draw(ball);
		window.display();

	}


	return 0;
}