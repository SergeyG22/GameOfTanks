#include "healthbar.h"

HealthBarTypeA::HealthBarTypeA() {
	healthbar_rectangle.emplace_back(new sf::RectangleShape);
	healthbar_rectangle.emplace_back(new sf::RectangleShape);
	healthbar_rectangle[0]->setSize(sf::Vector2f(160, 15));
	healthbar_rectangle[1]->setSize(sf::Vector2f(160, 15));
	healthbar_rectangle[0]->setFillColor(sf::Color::Red);	
	healthbar_rectangle[1]->setFillColor(sf::Color::Green);
}