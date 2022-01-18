#include "../../include/healthbar.h"

HealthBarTypeA::HealthBarTypeA() {
	healthbar_rectangle.emplace_back(new sf::RectangleShape);
	healthbar_rectangle.emplace_back(new sf::RectangleShape);
	healthbar_rectangle[0]->setSize(sf::Vector2f(160, 15));
	healthbar_rectangle[1]->setSize(sf::Vector2f(160, 15));
	healthbar_rectangle[0]->setFillColor(sf::Color::Red);	
	healthbar_rectangle[1]->setFillColor(sf::Color::Green);
}

void HealthBarTypeA::set_position(double current_position_x, double current_position_y) {
	for (const auto& it : healthbar_rectangle) {
		(*it).setPosition(current_position_x - dislocation_x, current_position_y - dislocation_y);
	}
}

void HealthBarTypeA::change_healthbar(float power_damage) {
	float healthbar_size = healthbar_rectangle[1]->getSize().x - power_damage;

	if (healthbar_size < 0) { healthbar_size = 0; }

	if (healthbar_rectangle[1]->getSize().x > 0) {
		healthbar_rectangle[1]->setSize(sf::Vector2f(healthbar_size, 15));
	}
}