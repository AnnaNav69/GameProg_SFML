// g++ Assigment_1.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_1/include -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib -lsfml-graphics -lsfml-system -lsfml-window

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class Circle {
public:
	sf::Text name;
	sf::CircleShape circle;
	float speedX;
	float speedY;

	Circle(sf::Text text, float X, float Y, float spX, float spY, int R, int G, int B, float rad)
	: name(text)
	, speedX (spX)
	, speedY (spY)
	{
		name.setPosition( X + rad - (name.getLocalBounds().width/2), Y + rad - name.getLocalBounds().height );
		circle = sf::CircleShape(rad);
		circle.setFillColor(sf::Color(R, G, B));
		circle.setPosition(X, Y);

	}

	~Circle(){};

	void move()
	{
		this->circle.setPosition(this->circle.getPosition() + sf::Vector2f(this->speedX, this->speedY));
		this->name.setPosition(this->name.getPosition() + sf::Vector2f(this->speedX, this->speedY));		
	}

	void draw(sf::RenderWindow & window) 
	{
		window.draw(this->circle);
		window.draw(this->name);
	}
};

class Rectangle {
public:
	sf::Text name;
	sf::RectangleShape rectangle;
	float speedX;
	float speedY;

	Rectangle(sf::Text text, float X, float Y, float spX, float spY, int R, int G, float B, float rWidth, float rHeight)
	: name(text)
	, speedX(spX)
	, speedY(spY)
	{
		name.setPosition(X + (rWidth - name.getLocalBounds().width)/2, Y + (rHeight - name.getLocalBounds().height)/2);

		rectangle = sf::RectangleShape(sf::Vector2f(rWidth, rHeight));
		rectangle.setFillColor(sf::Color(R, G, B));
		rectangle.setPosition(X, Y);
	}

	~Rectangle(){};

	void move()
	{
		this->rectangle.setPosition(this->rectangle.getPosition() + sf::Vector2f(this->speedX, this->speedY));
		this->name.setPosition(this->name.getPosition() + sf::Vector2f(this->speedX, this->speedY));		
	}

	void draw(sf::RenderWindow & window) 
	{
		window.draw(this->rectangle);
		window.draw(this->name);
	}
};

void readFile(std::string path, int & wWidth, int & wHeight, sf::Font & font,
	          std::vector<Circle> & circ, std::vector<Rectangle> & rect)
{
	std::string type;
	std::string fontPath;

	std::string shapeName;
	sf::Text    shapeTitle;

	int         fontHeight;
	int         fontRed;
	int         fontGreen;
	int         fontBlue;
	float       posX;
	float       posY;
	float       speedX;
	float       speedY;
	int         red;
	int         green;
	int         blue;
	float       size1;
	float       size2;

	std::ifstream read (path);
	read >> type >> wWidth >> wHeight;
	read >> type >> fontPath >> fontHeight >> fontRed >> fontGreen >> fontBlue;

	if (!font.loadFromFile(fontPath)) 
	{
		std::cerr << "Could not load font \n";
		exit (-1);
	}

	while (read >> type)
	{
		if (type == "Circle")
		{
			read >> shapeName >> posX >> posY >> speedX >> speedY >> red >> green >> blue >> size1;
			shapeTitle = sf::Text(shapeName, font, fontHeight);
			shapeTitle.setFillColor(sf::Color(fontRed,fontGreen, fontBlue));
			circ.push_back( Circle(shapeTitle, posX, posY, speedX, speedY, red, green, blue, size1) );
		}

		if (type == "Rectangle")
		{
			read >> shapeName >> posX >> posY >> speedX >> speedY >> red >> green >> blue >> size1 >> size2;
			shapeTitle = sf::Text(shapeName, font, fontHeight);
			shapeTitle.setFillColor(sf::Color(fontRed,fontGreen, fontBlue));
			rect.push_back( Rectangle(shapeTitle, posX, posY, speedX, speedY, red, green, blue, size1, size2) );
		}
	}

}




int main() 
{
	std::string filePath = "shapes_config.txt";
	int wWidth;
	int wHeight;

	std::vector<Circle>    circles;
	std::vector<Rectangle> rectangles;
	sf ::Font              myFont;

	readFile(filePath, wWidth, wHeight, myFont, circles, rectangles);

	sf::RenderWindow window (sf::VideoMode(wWidth, wHeight), "Assigment 1");

	// sf::CircleShape circle(50);
	// circle.setFillColor(sf::Color(255, 255, 100));
	// circle.setPosition(300.0f, 300.0f);
	// float circleMoveSpeed = 0.01f;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if(event.type == sf::Event::KeyPressed)
			{
				std::cout << "Key pressed with code: " << event.key.code << std::endl;

				if(event.key.code == sf::Keyboard::X)
				{
					// circleMoveSpeed = circleMoveSpeed * (-1.0f);
					// std::cout << "circleMoveSpeed = " << circleMoveSpeed << std::endl;
				}
			}
		}

		window.clear();

		for (auto & a : circles)
		{
			// a.move();
			a.draw(window);
		}

		for (auto & b : rectangles)
		{
			// b.move();
			b.draw(window);
		}

		window.display();
	}
	return 0;
}
