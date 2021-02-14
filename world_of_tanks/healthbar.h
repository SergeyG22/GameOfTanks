#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class HealthBar {

public:
	virtual ~HealthBar() { };
	virtual std::vector<std::unique_ptr<sf::RectangleShape>>& get_healthbar_rectangle()= 0;
	virtual void set_position(double current_position_x, double current_position_y) = 0;
	virtual void change_healthbar(float power_damage) = 0;
};

class HealthBarTypeA: public HealthBar {
	std::vector<std::unique_ptr<sf::RectangleShape>>healthbar_rectangle;
	double dislocation_x = 90;
	double dislocation_y = 130;    
public:
	HealthBarTypeA();
	std::vector<std::unique_ptr<sf::RectangleShape>>& get_healthbar_rectangle()override { return healthbar_rectangle; };
	void set_position(double current_position_x, double current_position_y)override {
		for (const auto& it : healthbar_rectangle) {
			(*it).setPosition(current_position_x - dislocation_x,current_position_y - dislocation_y);
		}
	}
	void change_healthbar(float power_damage) {

		float healthbar_size = healthbar_rectangle[1]->getSize().x - power_damage;

		if (healthbar_size < 0) {
			healthbar_size = 0;
		}

		if (healthbar_rectangle[1]->getSize().x > 0) {
			healthbar_rectangle[1]->setSize(sf::Vector2f(healthbar_size, 15));
		}
	}                     
};

