#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
	srand((unsigned)time(0));

	// Stores all the positions of the bricks
	std::vector<std::pair<float, float>> Bricks(16);

	float y = 30.0f;
	float x = 0.0f;
	for (int i = 0; i < 15; i++)
	{
		Bricks[i].first = x * 50.0f + 75.0f;
		Bricks[i].second = y;
		x++;
		if ((i + 1) % 5 == 0)
		{
			y += 30.0f;
			x = 0.0f;
		}
	}

	//Pong Slider Thingy Thing
	std::pair<float, float> ass;
	ass.first = 0; ass.second = 550;
	Bricks[15] = ass;

	sf::RenderWindow window (sf::VideoMode(400, 600), "Brick Bracker");

	sf::RectangleShape rs(sf::Vector2f(50.0f, 30.0f));
	sf::CircleShape cs(12.5, 12.5);
	cs.setPosition(sf::Vector2f(200, 175));

	int score = 0;
	float Xvel = float(rand() % 3 + 1), Yvel = float(rand() % 3 + 1);

	sf::Clock clock;
	float Ttime = 0.0f;

	while (window.isOpen())
	{
		Ttime += clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			switch (event.key.code)
			{
			case sf::Keyboard::Left:
				if (!(Bricks[15].first < 1.0f))
				{
					Bricks[15].first -= 10;
				}
				break;
			case sf::Keyboard::Right:
				if (!(Bricks[15].first > 324.0f))
				{
					Bricks[15].first += 10;
				}
				break;
			}
		}

		if (Ttime > 0.007f)
		{
			cs.move(Xvel, Yvel);
			Ttime = 0;

			if (cs.getPosition().x < 1.0f || cs.getPosition().x > 359.0f)
				Xvel = -Xvel;
			if (cs.getPosition().y < 1.0f)
				Yvel = -Yvel;
		}

		if (cs.getPosition().y > 600.0f || score == 15)
			if (score == 15)
			{	std::cout << "You Win!"; window.close();	}
			else
			{	std::cout << "Score: " << score; window.close();	}

		window.clear();
		for (int i = 0; i < 16; i++) 
		{
			// Brick and Slider Collision
			if (cs.getPosition().x + 25.0f > Bricks[i].first && cs.getPosition().x < Bricks[i].first + 75.0f &&
				cs.getPosition().y + 25.0f > Bricks[i].second && cs.getPosition().y < Bricks[i].second + 10.0f)
			{
				if (i != 15)
				{
					Bricks[i].first = 400; Bricks[i].second = 600; score++;
				}

				// Bounce
				if (cs.getPosition().x - Bricks[i].first + 50.0f >= cs.getPosition().y + 25.0f - Bricks[i].second)
				{	Yvel = -Yvel; cs.move(0, Yvel);	}
				if (cs.getPosition().x - Bricks[i].first + 50.0f <= cs.getPosition().y + 25.0f - Bricks[i].second)
				{	Xvel = -Xvel; cs.move(Xvel, 0);	}

				// So you can't get multiple at once
			}

			rs.setPosition(Bricks[i].first, Bricks[i].second);
			if (i == 15)
				rs.setSize(sf::Vector2f(75.0f, 10.0f));
			window.draw(rs);
		}
		rs.setSize(sf::Vector2f(50.0f, 30.0f));
		window.draw(cs);
		window.display();
	}
}