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
	std::vector<std::unique_ptr<sf::RectangleShape>>& get_healthbar_rectangle()override { return healthbar_rectangle; };
	void set_position(double current_position_x, double current_position_y)    override;
	void change_healthbar(float power_damage)                                  override;
	double dislocation_x = 90;
	double dislocation_y = 130;    
public:
	HealthBarTypeA();
};

