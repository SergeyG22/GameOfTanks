#pragma once
#include <SFML/Graphics.hpp>

class HealthBar {

public:
	virtual ~HealthBar() { };
	virtual sf::RectangleShape get_green_shape() = 0;
	virtual sf::RectangleShape get_red_shape() = 0;
};

class HealthBarTypeA: public HealthBar {
	sf::RectangleShape green_rectangle;
	sf::RectangleShape red_rectangle;
public:
	HealthBarTypeA();
	sf::RectangleShape get_green_shape()override { return green_rectangle; };
	sf::RectangleShape get_red_shape()override { return red_rectangle; };
};